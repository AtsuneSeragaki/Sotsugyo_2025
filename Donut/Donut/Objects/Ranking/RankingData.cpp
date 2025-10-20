#include "RankingData.h"
#include <stdio.h>
#include <string.h>

RankingData::RankingData()
{
	for (int i = 0; i < RANKING_DATA_MAX; i++)
	{
		rank[i] = NULL;
		score[i] = NULL;
	}
}

RankingData::~RankingData()
{
}

void RankingData::Initialize()
{
	// �����L���O�f�[�^�̓ǂݍ���
	FILE* fp = nullptr;

	// �t�@�C���I�[�v��
	errno_t result = fopen_s(&fp, "Resource/Data/ranking_data.txt", "r");

	// �G���[�`�F�b�N
	if (result != 0)
	{
		throw("Resource/Data/ranking_data.txt���J���܂���ł���\n");
	}

	// �Ώۃt�@�C������ǂݍ���
	for (int i = 0; i < RANKING_DATA_MAX; i++)
	{
		fscanf_s(fp, "%d %d", &rank[i], &score[i]);
	}

	// �t�@�C���N���[�Y
	fclose(fp);
}

void RankingData::Finalize()
{

}

void RankingData::SetRankingData(int score)
{
	if (this->score[RANKING_DATA_MAX - 1] < score)
	{
		this->score[RANKING_DATA_MAX - 1] = score;

		SortData();
	}
}

void RankingData::SortData()
{
	// �I��@�\�[�g���g�p���A�~���œ���ւ���
	for (int i = 0; i < RANKING_DATA_MAX - 1; i++)
	{
		for (int j = i + 1; j < RANKING_DATA_MAX; j++)
		{
			if (score[i] < score[j])
			{
				int tmp = score[i];
				score[i] = score[j];
				score[j] = tmp;
			}
		}
	}

	// ���ʂ𐮗񂳂���
	for (int i = 0; i < RANKING_DATA_MAX; i++)
	{
		rank[i] = 1;
	}
	for (int i = 0; i < RANKING_DATA_MAX - 1; i++)
	{
		for (int j = i + 1; j < RANKING_DATA_MAX; j++)
		{
			if (score[i] > score[j])
			{
				rank[j]++;
			}
		}
	}

	// �����L���O�f�[�^�̏�������
	FILE* fp = nullptr;

	// �t�@�C���I�[�v��
	errno_t result = fopen_s(&fp, "Resource/Data/ranking_data.txt", "w");

	// �G���[�`�F�b�N
	if (result != 0)
	{
		throw("Resource/Data/ranking_data.txt���J���܂���ł���\n");
	}

	// �Ώۃt�@�C���ɏ�������
	for (int i = 0; i < RANKING_DATA_MAX; i++)
	{
		fprintf(fp, "%d %d\n", rank[i],score[i]);
	}

	// �t�@�C���N���[�Y
	fclose(fp);
}
