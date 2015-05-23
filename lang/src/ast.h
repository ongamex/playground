#pragma once

#include <iostream>
#include <vector>

enum NodeType
{
	NT_None,

	NT_Num,
	NT_Var,

	NT_Add,
	NT_Sub,
	NT_Mul,
	NT_Div,

	NT_If,

	NT_NtList, // a list of nodes
};

struct Node
{
	Node() : type(NT_Num) {}

	Node(float number) {
		type = NT_Num;
		fData = number;;
	}

	Node(const NodeType type, std::initializer_list<Node*> nodes) : type(type), nodes(nodes) {}

	void printDepth(int depth) const {
		while(depth--) std::cout << "  ";
	}

	void printMe(const int depth) const
	{
		std::cout << std::endl;
		printDepth(depth);
		if(type == NT_Num)
		{
			std::cout << "num = " << fData;
		}
		else if(type == NT_Add){std::cout << "+";nodes[0]->printMe(depth+1); nodes[1]->printMe(depth+1);}
		else if(type == NT_Sub){std::cout << "-";nodes[0]->printMe(depth+1); nodes[1]->printMe(depth+1);}
		else if(type == NT_Mul){std::cout << "*";nodes[0]->printMe(depth+1); nodes[1]->printMe(depth+1);}
		else if(type == NT_Div){std::cout << "/";nodes[0]->printMe(depth+1); nodes[1]->printMe(depth+1);}
		else if(type == NT_If) {std::cout << "if (expr) stmt"; nodes[0]->printMe(depth+1); nodes[1]->printMe(depth+1);}
		else if(type == NT_NtList)
		{
			std::cout << "node list:";
			for(const auto& node : nodes) node->printMe(depth+1);
		}
		else std::cout << "Found node type=" << type;
	}

	union {
		float fData;
		char strData[32];
	};

	NodeType type;
	std::vector<Node*> nodes;
};

struct Ast
{
	inline Node* add(Node* node) {
		nodes.push_back(node);
		return node;
	}

	std::vector<Node*> nodes;
};

extern Ast g_ast;
