#pragma once
// �����J�[�̓��͂�ݒ�
// �f�o�b�O�ƃ����[�X�œ��͂���t�@�C�����Ⴄ�ł��̂悤�ɂ��Ă��܂��B
#ifdef _DEBUG
#define CV_EXT "d.lib"
#else
#define CV_EXT ".lib"
#endif
#pragma comment(lib, "opencv_core320" CV_EXT)       //�摜�E�s��f�[�^�\���̒񋟁A���[�e�B���e�B�@�\�Ȃ�
#pragma comment(lib, "opencv_highgui320" CV_EXT)    //GUI�i�E�B���h�E�\���Ȃǁj
#pragma comment(lib, "opencv_imgcodecs320" CV_EXT)  //�摜�t�@�C�����o��
#pragma comment(lib, "opencv_imgproc320" CV_EXT)    //�t�B���^�[�����A�G�b�W���o�Ȃ�
