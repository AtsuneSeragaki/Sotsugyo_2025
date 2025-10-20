#pragma once

#define RANKING_DATA_MAX 5

class RankingData
{
private:
	int rank[RANKING_DATA_MAX];   // �����N
	int score[RANKING_DATA_MAX];  // �X�R�A

public:

	// �R���X�g���N�^
	RankingData();

	// �f�X�g���N�^
	~RankingData();

	// ��������
	void Initialize();

	// �I������
	void Finalize();

	// �����L���O�f�[�^�̐ݒ�
	void SetRankingData(int score);

	// �X�R�A�擾����
	int GetScore(int value) const { return score[value]; }

	// �����N�擾����
	int GetRank(int value) const { return rank[value]; }

private:
	// �f�[�^����ւ�����
	void SortData();
};