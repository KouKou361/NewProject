#include "NodeBase.h"
#include "BehaviorData.h"
#include "EnemyBase.h"
#include <assert.h>

NodeBase* NodeBase::SearchNode(std::string searchName)
{
	if (name == searchName)return this;

	//一応　子供クラスでも検索をかける
	for (int i = 0; i < children.size(); i++)
	{
		NodeBase* child = GetChild(i)->SearchNode(searchName);

		if (child == nullptr)continue;

		if (child->name == searchName)
		{
			return child;
		}
	}

	assert("検索にヒットしなかった");
	return nullptr;
}

ActionBase::State NodeBase::Run(Charactor* enemy)
{
	if (enemy)
	{
		//もしターゲットがいなくなっていたら
		if (enemy->GetTarget() == nullptr)
		{
			return action->DeleteTarget();
		}


		return action->Run();
	}
	
		
	else 	return ActionBase::State::Failed;
}

//ノード推論
NodeBase* NodeBase::Inference(BehaviorData* data)
{
	
	std::vector<NodeBase*> list;
	list.clear();
	NodeBase* result = nullptr;

	
	//子ノードで実行可能なノードを探す
	
	
	for (int i = 0; i < children.size(); i++)
	{
		if (children.at(i)->judgement != nullptr)
		{
			if (children.at(i)->judgement->Judgement())
			{
				list.emplace_back(children.at(i).get());
			}
		}
		else {
			// 判定クラスがなければ無条件に追加
			list.emplace_back(children.at(i).get());
		}
	}

	//ルールの分岐
	switch (selectRule)
	{
		//優先順位
	case BehaviorTree::SelectRule::Priority:
		result=SelectPriority(&list);
		break;
		//ランダム
	case BehaviorTree::SelectRule::Random:
		result = SelectRandom(&list);
		break;
		//シーケンス
	case BehaviorTree::SelectRule::Sequence:
		result = SelectSequence(&list, data);
		break;
		//ONOFF
	case BehaviorTree::SelectRule::OnOff:
		result = SelectOnOff(&list);
		break;
	}
	if (result!=nullptr)
	{
		//行動があるなら終了処理
		if (result->action != nullptr)
		{
			//行動開始処理
			result->NodeActionStart();
			return result;
		}
		else
		{
			return result = result->Inference(data);
		}



	}
	return result;

}
//ノードのアクション
//bool NodeBase::Run()
//{
//	ActionBase::State state=
//}
//ランダムに一つ選択する
NodeBase* NodeBase::SelectRandom(std::vector<NodeBase*> *list)
{
	int rnd = rand() % list->size();
	return list->at(rnd);
}
//優先順位で選択する
NodeBase* NodeBase::SelectPriority(std::vector<NodeBase*> *list)
{
	int MaxPriority = INT_MAX;
	NodeBase* SelectNode=nullptr;

	for (int i = 0; i < list->size(); i++)
	{
		if (MaxPriority >= list->at(i)->GetPriority())
		{
			SelectNode=list->at(i);
			MaxPriority = list->at(i)->GetPriority();
		}
		
	}
	return SelectNode;
}

// シーケンス
NodeBase* NodeBase::SelectSequence(std::vector<NodeBase*>* list, BehaviorData* data)
{
	// シーケンス処理でノードを指定するコードを自分で考えて補完してください。
	// ヒントとして手順を記載しています。
	// 手順①：現在のノードのシーケンスのステップを取得
	//		   ステップはint型、シーケンスステップの取得にはdata->GetSequenceStep()を使用すること
	int step = 0;
	step = data->GetSequenceStep(GetName());

	// 手順①で取得したステップ数が子ノード数を超えているか
	if (step >= (int)children.size())
	{
		if (selectRule == BehaviorTree::SelectRule::SequentialLooping)step = 0;
		else return NULL;
		// 手順②：selectRuleがSEQUENTIAL_LOOPINGの場合、stepに0を代入
		// 		  それ以外はNULLをリターンしなさい
	}

	// ③step番号のノードを検索
	for (auto itr = list->begin(); itr != list->end(); itr++)
	{
		//自身の子ノードのstep番目のノードが、現在の実行可能ノードにあるか検索
		if (children.at(step)->GetName() == (*itr)->GetName())
		{

			// ④検索した結果、該当データがあれば自身をdataのsequenceStackに追加
			data->PushSequenceNode(this);
			// ⑤data->setSequenceStepでgetName()のキーデータにステップ＋１をセットする
			data->SetSequenceStep(GetName(), step + 1);
			// ⑥自身の子ノードのstep番目のノードをリターン
			return children.at(step).get();
		}
	}

	return NULL;
}

//一度も選択されたことがない場合　それを選択する
//しかしすべて一通り選択されたことがあるならSelectPriority()で選択する。
NodeBase* NodeBase::SelectOnOff(std::vector<NodeBase*>* list)
{
	int MaxPriority = INT_MAX;
	NodeBase* SelectNode = nullptr;

	for (int i = 0; i < list->size(); i++)
	{
		//選択されたことがない場合
		if (list->at(i)->OldSelect==false)
		{
			list->at(i)->OldSelect = true;
			return list->at(i);
		}


		if (MaxPriority >= list->at(i)->GetPriority())
		{
			SelectNode = list->at(i);
			MaxPriority = list->at(i)->GetPriority();
		}

	}
	return SelectNode;
}
