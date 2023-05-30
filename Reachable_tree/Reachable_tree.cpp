// Reachable_tree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<thread>
#include"read_data.h"
#include"PN.h"
#include"search_tree.h"
#include"output.h"
vector<int> get_goal_vector(vector<int>& goalMarking, vector<int>& goalPlace, int nums) {
	vector<int> ans(nums, 0);
	if (goalMarking.size() != goalPlace.size())
	{
		std::cout << "The dimension of goal marking and goal place is not consistent!" << std::endl;
		exit(-1);
	}
	for (int i = 0; i < goalPlace.size(); ++i) {
		ans[goalPlace[i]] = goalMarking[i];
	}
	return ans;
}

int main()
{
	//读数据
	std::vector<int> m0 = read_vector<int>(M0_path);
	int num = m0.size();
	std::vector<int> d0 = read_vector<int>(Time_path);
	std::vector<vector<int>> pre = read_matrix(Pre_path, num);
	std::vector<vector<int>> post = read_matrix(Post_path, num);

	std::vector<int> goals = read_vector<int>(GoalPlace);
	std::vector<int> goal_marking = read_vector<int>(GoalMarking);

	//开始搜索树
	auto goal_vector = get_goal_vector(goal_marking, goals, num);
	SearchTree tree(m0, d0, pre, post, goal_vector, 1);
	tree.run();
	
	tree.BackTree();
	tree.BackDeadlock();
	std::thread t1(output_gv, std::ref(tree));
	std::thread t2(output_py, std::ref(tree), num);
	t1.join();
	t2.join();
	output_gv(tree);
	//output_py(tree, num);
	std::cout << tree.goal_nodes_.size() << std::endl;
	std::cout << sizeof(Node) << std::endl;
}
