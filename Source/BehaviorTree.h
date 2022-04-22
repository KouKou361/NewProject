#pragma once

#include <string>
#include <memory>


using namespace std;

class Charactor;
class NodeBase;
class BehaviorData;
class JudgementBase;
class ActionBase;

//操作専用
class BehaviorTree
{
public:
	//選択ルール
	enum class SelectRule
	{
		NONE,
		PRIORITY,//優先順位
		SEQUENCE,//シーケンス
		SEQUETIAL_LOOPING,
		RANDOM,//ランダム
		ON_OFF,//ON,OFF

	};
public:
	BehaviorTree();
	virtual ~BehaviorTree() {};

	//ノードの追加
	void AddNode(const std::string searchName, const std::string entryName, const int priority, const SelectRule selectRule, JudgementBase* judgment, ActionBase* action, const bool onOff=false);
	// 実行ノードを推論する
	NodeBase* ActiveNodeInference(Charactor* enemy, BehaviorData* data);
	//実行
	NodeBase* Run(Charactor* enemy,NodeBase* actionNode, BehaviorData* data);


private:
	// ノード全削除
	void NodeAllClear(NodeBase* delNode);

	NodeBase* SequenceBack(NodeBase* sequenceNode, Charactor* enemy, BehaviorData* data);
private:
	// ルートノード
	std::shared_ptr<NodeBase> root;
};
