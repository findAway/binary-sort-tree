/*
 * 二叉排序树的实现 2017.12.7
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 定义二叉树的节点结构
 */
typedef struct tagTreeNode
{
    int nData;
    struct tagTreeNode* lchild;
    struct tagTreeNode* rchild;
} TreeNode;

/*
 * 按节点值从小到大打印二叉树
 */
void DumpTree(TreeNode* ptRootNode)
{
    if (ptRootNode == 0)
    {
        return;
    }

    if (ptRootNode->lchild != 0)
    {
        DumpTree(ptRootNode->lchild);
    }

    printf("node:%p, left:%p, right:%p, data:%d\n", ptRootNode, ptRootNode->lchild, ptRootNode->rchild, ptRootNode->nData);

    if (ptRootNode->rchild != 0)
    {
        DumpTree(ptRootNode->rchild);
    }
}

/*
 * 二叉排序树插入操作 
 */
TreeNode* InsertTree(TreeNode* ptRootNode, int nData)
{
    TreeNode* pNode = ptRootNode;
    if (pNode == 0)
    {
        pNode = malloc(sizeof(TreeNode));
        pNode->nData = nData;
        pNode->lchild = 0;
        pNode->rchild = 0;
        return pNode;
    } 

    while (1)
    {
        if (nData < pNode->nData)
        {
            if (pNode->lchild == 0)
            {
                //左节点不存在，则创建并存入值，返回
                TreeNode* pNewNode = malloc(sizeof(TreeNode));
                pNewNode->nData = nData;
                pNewNode->lchild = 0;
                pNewNode->rchild = 0;
                pNode->lchild = pNewNode;
                break;
            }
            else
            {
                pNode = pNode->lchild;
            }
        }
        else
        {
            if (pNode->rchild == 0)
            {
                //左节点不存在，则创建并存入值，返回
                TreeNode* pNewNode = malloc(sizeof(TreeNode));
                pNewNode->nData = nData;
                pNewNode->lchild = 0;
                pNewNode->rchild = 0;
                pNode->rchild = pNewNode;
                break;
            }
            else
            {
                pNode = pNode->rchild;
            }
        }
    }

    return ptRootNode;
}

/*
 * 删除二叉树中值为nData的节点
 */
void DeleteNode(TreeNode* pRootNode, int nData)
{
    if (pRootNode == 0)
    {
        return;
    }

    TreeNode* pNode = pRootNode;
    while (1)
    {
        if (!pNode)
        {
            break;
        }

        if (nData < pNode->nData)
        {
            pNode = pNode->lchild;
        }
        else if (nData > pNode->nData)
        {
            pNode = pNode->rchild;
        }
        else
        {
            if (!pNode->lchild && !pNode->rchild)
            {
                //todo
            }
        }
    }
}

int main()
{
    TreeNode* pBinOrderTree = 0;  //此节点指向二叉树的根节点，表示一颗二叉树

    //定义一个数组并用数值初始化，之后将数值各成员的值存入二叉树
    int acData[] = {44, 32, 31, 66, 50, 13, 80, 72, 35, 43, 92, 100};

    for (int nIndex = 0; nIndex < sizeof(acData)/sizeof(int); nIndex++)
    {
        pBinOrderTree = InsertTree(pBinOrderTree, acData[nIndex]);
    }

    DumpTree(pBinOrderTree);

    return 0;
}
