#pragma once
#include<string>
#include"scene.h"

namespace SceneManager {
	void Init()								;
	void Update()							;
	void Draw()								;
	void Delete()							;

	/// <summary>
	/// �V�[���̐؂�ւ��֐�
	/// </summary>
	/// <param name="sceneName">�V�[���̖��O</param>
	void SceneChange(std::string sceneName)	;
	/// <summary>
	/// <para>�t���[���J�E���^�[</para>
	/// <para>�Q�[�����n�܂��Ă���̃t���[�����擾</para>
	/// </summary>
	/// <returns></returns>
	int GetFrame()							;

	/// <summary>
	/// �Q�[���I���t���O
	/// </summary>
	/// <param name="true	">�I��</param>
	/// <param name="false	">���s</param>
	/// <returns></returns>
	bool GameEnd()							;
	/// <summary>
	/// �Q�[�����I������
	/// </summary>
	void SetGameEnd();
	/// <summary>
	/// Common �V�[�����擾
	/// </summary>
	/// <returns></returns>
	Scene* GetCommonScene()					;
	/// <summary>
	/// Current �V�[�����擾
	/// </summary>
	/// <returns></returns>
	Scene* GetCurrentScene()				;
	/// <summary>
	/// ���݃V�[���̖��O���擾
	/// </summary>
	/// <returns></returns>
	std::string GetCurrentSceneName()		;
}