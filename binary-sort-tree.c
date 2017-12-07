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

    printf("node:%10p, left:%10p, right:%10p, data:%d\n", ptRootNode, ptRootNode->lchild, 
            ptRootNode->rchild, ptRootNode->nData);

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
TreeNode* DeleteNode(TreeNode* pRootNode, int nData)
{
    if (pRootNode == 0)
    {
        printf("this tree is empty\n");
        return 0;
    }

    TreeNode* pNode = pRootNode;
    TreeNode** ppContainer = 0;
    TreeNode* pRetNodeMaybe = 0;  //树的根节点可能改变，此变量记录可能的新的树根节点

    while (1)
    {
        if (!pNode)
        {
            break;
        }

        if (nData < pNode->nData)
        {
            ppContainer = &(pNode->lchild);
            pNode = pNode->lchild;
        }
        else if (nData > pNode->nData)
        {
            ppContainer = &(pNode->rchild);
            pNode = pNode->rchild;
        }
        else
        {
            //如果是叶子节点，可直接删除
            if (!pNode->lchild && !pNode->rchild)
            {
                if (ppContainer)
                {
                    *ppContainer = 0;
                }

                pRetNodeMaybe = 0;
                break;
            }

            //仅有左节点的情况
            if (!pNode->rchild)
            {
                if (ppContainer)
                {
                    *ppContainer = pNode->lchild;
                }

                pRetNodeMaybe = pNode->lchild;
                break;
            }

            //仅有右节点的情况
            if (!pNode->lchild)
            {
                if (ppContainer)
                {
                    *ppContainer = pNode->rchild;
                }

                pRetNodeMaybe = pNode->rchild;
                break;
            }

            //既有左节点，也有右节点的情况，查找直接后继替换其位置
            //先查找直接后继
            TreeNode* child = pNode->rchild;
            TreeNode* father = 0;
            while (child->lchild)
            {
                father = child;
                child = child->lchild;
            }

            if (father) //直接后继非右节点的情况
            {
                father->lchild = child->rchild;
                child->lchild = pNode->lchild;
                child->rchild = pNode->rchild;
            }
            else //直接后继就是右节点的情况
            {
                child->lchild = pNode->lchild;
            }

            if (ppContainer)
            {
                *ppContainer = child;
            }

            pRetNodeMaybe = child;
            break;
        }
    }

    if (!pNode)
    {
        printf("%d not found in this tree\n", nData);
        return pRootNode;
    }

    //如果删除的节点为根节点的话，那么树的根节点会改变
    if (pNode == pRootNode)
    {
        free(pNode);
        return pRetNodeMaybe;
    }

    free(pNode);
    return pRootNode;
}

int main()
{
    TreeNode* pBinOrderTree = 0;  //此节点指向二叉树的根节点，表示一颗二叉树

    //定义一个数组并用数值初始化，之后将数值各成员的值存入二叉树
    int acData[] = {44, 32, 31, 66, 50, 13, 80, 72, 74, 35, 43, 92, 100};

    for (int nIndex = 0; nIndex < sizeof(acData)/sizeof(int); nIndex++)
    {
        pBinOrderTree = InsertTree(pBinOrderTree, acData[nIndex]);
    }

    DumpTree(pBinOrderTree);

    //删除节点测试
#if 0
    pBinOrderTree = DeleteNode(pBinOrderTree, 44);
    printf("DeleteNode ret:%10p\n", pBinOrderTree);
    if (pBinOrderTree)
    {
        DumpTree(pBinOrderTree);
    }

    pBinOrderTree = DeleteNode(pBinOrderTree, 50);
    printf("DeleteNode ret:%10p\n", pBinOrderTree);
    if (pBinOrderTree)
    {
        DumpTree(pBinOrderTree);
    }

    pBinOrderTree = DeleteNode(pBinOrderTree, 92);
    printf("DeleteNode ret:%10p\n", pBinOrderTree);
    if (pBinOrderTree)
    {
        DumpTree(pBinOrderTree);
    }
#endif

    pBinOrderTree = DeleteNode(pBinOrderTree, 66);
    printf("DeleteNode ret:%10p\n", pBinOrderTree);
    if (pBinOrderTree)
    {
        DumpTree(pBinOrderTree);
    }

    pBinOrderTree = DeleteNode(pBinOrderTree, 166);
    printf("DeleteNode ret:%10p\n", pBinOrderTree);

    return 0;
}
