#pragma once

#include<string>
#include<vector>


class CsvSave {
public:
	/// <summary>
	/// <para>CSV�t�@�C���̓ǂݍ���</para>
	/// <para>�ǂݍ��񂾒l��S�ĕ����񂵂ɕԂ�</para>
	/// </summary>
	/// <param name="pass	">�ǂݍ���.csv�̃t�@�C���p�X</param>
	/// <returns></returns>
	static std::vector<std::string> Load(std::string pass);

	/// <summary>
	/// <para>�t�@�C���̏����o��</para>
	/// <para></para>
	/// </summary>
	/// <param name="pass	">�����o��.csv�̃t�@�C���p�X</param>
	/// <param name="str	">�����o��.csv�̃t�@�C����[.csv�܂œ����]</param>
	/// <param name="CRLF	">���s����܂ł̂P�s�̕�����</param>
	/// <returns></returns>
	static void Save(std::string pass, std::vector<std::string>str,int CRLF=10);
private:
};