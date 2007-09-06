#include "inc\mc.h"
#include "inc\zslib.h"
#include "inc\mui.h"
#include "inc\encode.h"

void ZipError(int zipErrNum, char* procName)
{
	sprintf(msgbuf, muitxt(ind_err_ziperr), zipErrNum, procName);
	MsgBoxError(1, (int)msgbuf);
}

void CloseZip(ZIPINF* pzi)
{
	if (pzi->uf)
	{
		FreeZipInfo(pzi);
		unzClose(pzi->uf);
		pzi->uf = 0;
		pzi->szCurDir[0] = '\0';
		pzi->szZipPath[0] = '\0';
	}
}

void CloseTabZip(int tab)
{
	CloseZip(tabs[tab]->zipInfo);
}

int IsZipOpened(int tab)
{
	return (tabs[tab]->zipInfo->uf != NULL);
}

int IsInZip()
{
	return IsZipOpened(curtab);
}

void FreeZipInfo(ZIPINF* pzi)
{
	if (pzi->pfi)
	{
		for (int i=0; i < pzi->gi.number_entry; i++)
			if (pzi->pfi[i]) mfree(pzi->pfi[i]);
		mfree(pzi->pfi);
		pzi->pfi = 0;
	}
	if (pzi->pszNames)
	{
		for (int i=0; i < pzi->gi.number_entry; i++)
			if (pzi->pszNames[i]) mfree(pzi->pszNames[i]);
		mfree(pzi->pszNames);
		pzi->pszNames = 0;
	}
	if (pzi->password)
	{
		mfree(pzi->password);
		pzi->password = 0;
	}
}


// ��������� � ��������� ���������� � ���������� ������ � ������
int ReadZipInfo(ZIPINF* pzi)
{
	int zerr = UNZ_OK;

	if (pzi->uf)
	{
		zerr = unzGetGlobalInfo(pzi->uf, &pzi->gi);
		if (zerr == UNZ_OK)
		{
			if (pzi->gi.number_entry > 0)
			{
				int useProgressBar = !progr_start;
				if (useProgressBar)
				{
					// ��������� �������� ���, ���� ��� �� ������� ������
					Busy = 1;
					initprogr(ind_msg_zreading);
					progr_max = pzi->gi.number_entry;
					incprogr(0);
				}
			
				int allocsize = pzi->gi.number_entry * sizeof(char*);
				pzi->pszNames = malloc(allocsize);
				if (pzi->pszNames)
				{
					zeromem(pzi->pszNames, allocsize);
					pzi->pfi = malloc(allocsize);
					if (pzi->pfi) zeromem(pzi->pfi, allocsize);
				}
				
				if (pzi->pszNames && pzi->pfi)
				{
					zerr = unzGoToFirstFile(pzi->uf);
					if (zerr == UNZ_OK)
					{
						for (int i=0; i < pzi->gi.number_entry && zerr == UNZ_OK && !progr_stop; i++)
						{
							pzi->pszNames[i] = malloc(MAX_PATH_INZIP);
							pzi->pfi[i] = malloc(sizeof(unz_file_info));
							if (pzi->pszNames[i] != NULL && pzi->pfi[i] != NULL)
							{
								zerr = unzGetCurrentFileInfo(pzi->uf, pzi->pfi[i], pzi->pszNames[i], MAX_PATH_INZIP,
									NULL, 0, NULL, 0);
								if (zerr == UNZ_OK)
								{
									// ������ �����
									strreplace(pzi->pszNames[i], '/', '\\');
									
									// ���������
									dos2utf8(pzi->pszNames[i]);
									
									// ��������� � ���������� �����
									if ((i+1) < pzi->gi.number_entry)
									{
										zerr = unzGoToNextFile(pzi->uf);
										if (zerr != UNZ_OK) ZipError(zerr, "unzGoToNextFile");
									}
								}
								else ZipError(zerr, "unzGetCurrentFileInfo");
							}
							else ZipError(zerr = UNZ_ERRNO, "no memory for fileinfo");
							
							if (useProgressBar) incprogr(1);
						}
					}
					else ZipError(zerr, "unzGoToFirstFile");
				}
				else ZipError(zerr = UNZ_ERRNO, "no memory");
				
				if (useProgressBar)
				{
					endprogr(); // ������������� �������� ���
					Busy = 0;
				}
			}
		}
		else ZipError(zerr, "unzGetGlobalInfo");
	}

	if (progr_stop) zerr = -11111;
	
	if (zerr != UNZ_OK) FreeZipInfo(pzi);

	return zerr;
}

int OpenZip(ZIPINF* pzi, char* zipFileName)
{
	int zerr = UNZ_OK;

	unzFile uf = unzOpen(zipFileName);
	if (uf != NULL)
	{
		pzi->uf = uf;
		pzi->szCurDir[0] = '\0';
		strcpy(pzi->szZipPath, zipFileName);
	}
	else zerr = UNZ_ERRNO;
	
	if (zerr == UNZ_OK)
		zerr = ReadZipInfo(pzi);
		
	if (zerr != UNZ_OK)
		CloseZip(pzi);	

	return zerr;
}

int OpenTabZip(int tab, char* zipFileName)
{
	int zerr = UNZ_ERRNO;

	if (!IsZipOpened(tab)) // �� ������������ ��������� ������
		zerr = OpenZip(tabs[tab]->zipInfo, zipFileName);

	return zerr;
}

int FillZipFiles(int tab, char* subdname)
{
	int num = 0;
	char buf[MAX_PATH_INZIP];
	char* pszDirName = subdname[0] == '\\' ? subdname + 1 : subdname; // ��������� � ������ �������� ���� 
	ZIPINF* pzi = tabs[tab]->zipInfo;

	if (pzi->uf)		
	{
		for (int i=0; i < pzi->gi.number_entry; i++)
		{
			int ignore = 1;
			int dirLen = strlen(pszDirName);
			strcpy(buf, pzi->pszNames[i]);
			char* pFileNameStart = &buf[0];
			unz_file_info* pfi = pzi->pfi[i];

			if (dirLen == 0)
			{
				// ���� ���� �������� ��������
				// �� ��������� ��� ����� � ������� ��� ������ '\' 
				char* slashPos = strstr(buf, "\\");
				ignore = (slashPos != NULL);
				if (ignore)
				{
					// � ��������� ��� ���������� - � ��� ���� ����, � ��� ���������
					ignore = (*(slashPos + 1) != 0);
					if (!ignore)
					{
						// ������ ���� ����, ����� �� ���������
						*slashPos = 0;
					}
				}
			}
			else
			{
				// ���������� ������, ���� ����� � ����� ���� - �� ��� �������� ����� ����������
				pFileNameStart = pFileNameStart + dirLen;
				ignore = (strnicmp(buf, pszDirName, dirLen) != 0 || *pFileNameStart != '\\');
				if (!ignore)
				{
					pFileNameStart = pFileNameStart + 1; // ��������� ���� ����� ����� ����������

					// ������� ���� �������, ����������
					ignore = (*pFileNameStart == 0);
					if (!ignore)
					{
						// �������� �� �������������
						char* pFileNameEnd = strstr(pFileNameStart, "\\");
						if (pFileNameEnd != NULL)
						{
							// �������� �� �� ��� ��� �� ���� ������������� � �� ��������, ���� ����������
							ignore = (*(pFileNameEnd+1) != 0);
							if (!ignore)
							{
								*pFileNameEnd = 0; // ������� ���� � �����
							}
						}
					}
				}
			}

			if (!ignore)
			{
				AddFile(tab, i, pFileNameStart, pfi->uncompressed_size, pfi->external_fa, pfi->dosDate,
					pfi->compressed_size, (pfi->external_fa & FA_DIRECTORY) ? TYPE_ZIP_DIR : TYPE_ZIP_FILE);
				num++;
			}
		}
	}

	return num;
}

int SetCurrentFileInZip(ZIPINF* pzi, int id)
{
	int zerr = unzGoToFirstFile(pzi->uf);
	if (zerr != UNZ_OK)
		return 1;
	
	for (int i = 1; i <= id; i++)
	{
		zerr = unzGoToNextFile(pzi->uf);
		if (zerr != UNZ_OK)
			return i + 1;
	}
	
	return 0;	
}

int ExtractCurrentFile(unzFile uf, char* filePathInZip, char* extractDir, int usePaths, char* password)
{
	int res = UNZ_OK;
	int fout = 0;
	char extractFilePath[MAX_PATH];
	char fnbuf[MAX_PATH];
	
	if (filePathInZip == NULL)
	{
		// ��������� ��� ���� ���� �����
		unz_file_info fi;
		filePathInZip = fnbuf;
		unzGetCurrentFileInfo(uf, &fi, filePathInZip, MAX_PATH, NULL, 0, NULL, 0);    
	}

	uInt size_buf = WRITEBUFFERSIZE;
	void* buf = (void*)malloc(size_buf);
	if (buf == NULL)
	{
		ZipError(1, "ExtractCurrentFile");
		return 1;
	}

	char* fileNameInZip = GetFileName(filePathInZip);
	if ((*fileNameInZip) == '\0')
	{
		if (usePaths)
		{
			// ����������... �������
			// ToDo: ��������� ��� �������� ���� ����� ����...
			sprintf(extractFilePath, _s_s, extractDir, filePathInZip);
			mktree(extractFilePath);
		}
	}
	else
	{
		// File
		if (usePaths)
			sprintf(extractFilePath, _s_s, extractDir, filePathInZip);
		else
			sprintf(extractFilePath, _s_s, extractDir, fileNameInZip);

		if (fexists(extractFilePath))
		{
			// ToDo: �������� �������� - ���� Temp, �� ������������ �� ���������, ����� - ������
			if (fsrm(extractFilePath, 0) != 0)
				ZipError(res = 2, "ExtractCurrentFile.fsrm");
		}

		if (res == UNZ_OK)
		{
			fout = fopen(extractFilePath, A_ReadWrite+A_Create+A_Truncate+A_BIN, P_READ+P_WRITE, &err);

			/* some zipfile don't contain directory alone before file */
			if (fout == -1 && usePaths && fileNameInZip != filePathInZip)
			{
				char c = *(fileNameInZip - 1);
				*(fileNameInZip - 1) = '\0';
				mktree(filePathInZip);
				*(fileNameInZip - 1) = c;
				fout = fopen(extractFilePath, A_ReadWrite+A_Create+A_Truncate+A_BIN, P_READ+P_WRITE, &err);
			}

			if (fout == -1)
				ZipError(res = 3, "ExtractCurrentFile.fopen");
		}

		if (res == UNZ_OK)
		{
			// ���������� ���������

			// ������� ����
			if (unzOpenCurrentFilePassword(uf, password) == UNZ_OK)
			{
				int cb = 0;
				do
				{
					cb = (int)unzReadCurrentFile(uf, buf, size_buf);
					if (cb < 0)
					{
						ZipError(cb, "ExtractCurrentFile.unzReadCurrentFile");
						res = 5;
						break;
					}
					else if (cb > 0)
					{
						if (fwrite(fout, buf, cb, &err) != cb)
						{
							ZipError(res = 6, "ExtractCurrentFile.fwrite");
							break;
						}
					}
				}
				while (cb > 0);

				if (fout) { fclose(fout, &err); fout = 0; }

				if (res == UNZ_OK)
				{
					// ���������� ���� ����� ������������ �����
					// change_file_date(write_filename, file_info.dosDate, file_info.tmu_date);
				}
			}
			else ZipError(res = 7, "ExtractCurrentFile.unzOpenCurrentFile");

			if (fout) fclose(fout, &err);
		}

		if (res == UNZ_OK)
		{
			if (unzCloseCurrentFile(uf) != UNZ_OK)
				ZipError(res = 8, "ExtractCurrentFile.unzCloseCurrentFile");
		}
		else unzCloseCurrentFile(uf); /* don't lose the error */
	}

	mfree(buf);
	return res;
} 

int ExtractFile(ZIPINF* pzi, char* fname, char* extractDir, int usePaths)
{
	// ��������������� �� ������ �����
	int found = 0;
	char buf[MAX_PATH + 1];
	strcpy(buf + 1, fname);
	buf[0] = '\\'; // � ������ ������� ���� �� ��� ������ ���� fname ��� �����
	char* nameWithoutSlash = ( (buf[1] == '\\') ? (buf + 2) : (buf + 1) );
	char* nameWithSlash = ( (buf[1] == '\\') ? (buf + 1) : (buf) );
	
	for (int i = 0; i < pzi->gi.number_entry; i++)
	{
		found = (stricmp(nameWithoutSlash, pzi->pszNames[i]) == 0);
		if (!found)
		{
			// ������� �������� �� ������
			found = (stricmp(nameWithSlash, pzi->pszNames[i]) == 0);
		}

		if (found)
		{
			// ��������� ���, ���� �����
			return ExtractFileByID(pzi, i, extractDir, usePaths);	 
		}
	}
	
	return 1;
}

int ExtractFileByID(ZIPINF* pzi, int id, char* extractDir, int usePaths)
{
	// ��������������� �� ������ �����
	if (SetCurrentFileInZip(pzi, id) == UNZ_OK)
	{
		// � ��������� ���
		return ExtractCurrentFile(pzi->uf, pzi->pszNames[id], extractDir, usePaths, pzi->password);	 
	}
	else return 1;
}

int ExtractDir(ZIPINF* pzi, char* dname, char* extractDir, int usePaths)
{
	int found = 0;
	char buf[MAX_PATH + 1];
	strcpy(buf + 1, dname);
	buf[0] = '\\'; // � ������ ������� ���� �� ��� ������ ���� fname ��� �����
	char* nameWithoutSlash = ( (buf[1] == '\\') ? (buf + 2) : (buf + 1) );
	char* nameWithSlash = ( (buf[1] == '\\') ? (buf + 1) : (buf) );
	
	int zerr = UNZ_OK;
	int dlen = strlen(nameWithoutSlash);

	// ���������� ��� �����
	for (int i = 0; i < pzi->gi.number_entry; i++)
	{
		if (i == 0) zerr = unzGoToFirstFile(pzi->uf);
		else zerr = unzGoToNextFile(pzi->uf);
			
		if (zerr) return zerr;
		
		// ��������� ���������� �� ��� ����� � ���� � ���� ����������, ���� �� - ���������
		found = (strnicmp(nameWithoutSlash, pzi->pszNames[i], dlen) == 0);
		if (!found)
		{
			// ������� �������� �� ������
			found = (strnicmp(nameWithSlash, pzi->pszNames[i], dlen + 1) == 0);
		}
			
		if (found)
			ExtractCurrentFile(pzi->uf, pzi->pszNames[i], extractDir, 1, pzi->password);
	}
	
	return zerr;
}

// ��� �� ���� :) ��� ����
ZIPINF zi;

void ZipBufferExtractBegin()
{
}

int ZipBufferExtract(FN_ITM* pi, char* extractDir)
{
	if (pi && pi->zipPath && pi->full)
	{
		ZIPINF* pzi = &zi;
		int usingZipFromTab = 0;
		
		for (int i = 0; i < MAX_TABS; i++)
		{
			if (IsZipOpened(i) && stricmp(tabs[i]->zipInfo->szZipPath, pi->zipPath) == 0)
			{
				// ���� ��� ������ � ����, �� ���������� ���
				pzi = tabs[i]->zipInfo;
				usingZipFromTab = 1;
				break;
			}
		}

		if (!usingZipFromTab)
		{
			// ���� ���� ��� ������, �� ����� �� ���������, �� ��������� ������
			if (pzi->uf != 0 && stricmp(pzi->szZipPath, pi->zipPath) != 0)
				CloseZip(pzi);

			// ���� ���� ��� �� ������ - �� ���������
			if (pzi->uf == 0)
				if (OpenZip(pzi, pi->zipPath) != UNZ_OK)
					return UNZ_ERRNO;
		}
				
		if (pi->ftype == TYPE_ZIP_FILE)
			return ExtractFile(pzi, pi->full, extractDir, 0);
		else if (pi->ftype == TYPE_ZIP_DIR)
			return ExtractDir(pzi, pi->full, extractDir, 1); 
	}
    
    return 0;
}

void ZipBufferExtractEnd()
{
	if (zi.uf != 0)
		CloseZip(&zi);
}
