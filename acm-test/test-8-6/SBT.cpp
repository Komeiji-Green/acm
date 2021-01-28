/*
maintain(T):
	If (s[T.left.left]>s[T.right]) Then
		// 情况1
		right-rotate(T) 
		// T的值会变为当前新的根节点，即例图中的L节点
		maintain(T.right)
		maintain(T)
	Elseif (s[T.left.right]>s[T.right]) Then
		// 情况2
		left-rotate(T.left)
		right-rotate(T)
		// T的值会变为当前新的根节点，即例图中的B节点
		maintain(T.left)
		maintain(T.right)
		maintain(T)
	Elseif (s[T.right.right]>s[T.left]) Then
		// 情况3
		left-rotate(T) // 此处T的值会发生改变
		maintain(T.left)
		maintain(T)
	Elseif (s[T.right.left]>s[T.left]) Then
		// 情况4
		right-rotate(T.right)
		left-rotate(T) // 此处T的值会发生改变
		maintain(T.left)
		maintain(T.right)
		maintain(T)
	End If
使用maintain的过程中，会出现很多重复检查的情况。

因此加入一个flag标记来避免重复检查。当flag标签为false时，我们只检查第1、2种情况；当flag标签为true时，只检查第3、4种情况。

得到精简版的maintain伪代码为：

maintain(T, flag):
	If (flag is false) Then
		If (s[T.left.left]>s[T.right]) Then
			// 情况1
			right-rotate(T) // 此处T的值会发生改变
		Elseif (s[T.left.right]>s[T.right]) Then
			// 情况2
			left-rotate(T.left)
			right-rotate(T) // 此处T的值会发生改变
		Else 
			// 已经满足SBT性质
			Return 
		End If
	Else
		If (s[T.right.right]>s[T.left]) Then
			// 情况3
			left-rotate(T) // 此处T的值会发生改变
		Elseif (s[T.right.left]>s[T.left]) Then
			// 情况4
			right-rotate(T.right)
			left-rotate(T) // 此处T的值会发生改变
		Else 
			// 已经满足SBT性质
			Return 
		End If
	End If
	maintain(T.left, false)
	maintain(T.right, true)
	maintain(T, false)
	maintain(T, true)
最后就是在什么地方使用maintain函数？很显然，当每次树的结构发生变化时，需要使用maintain来修正，而这两种情况主要是插入一个新的节点，或是删除一个节点。

插入一个新节点：

insert(T, key):
	// 基本和普通的二叉搜索树插入相同
	If (T is empty) Then
		T = new Node(key)
	Else 
		s[T] = s[T] + 1
		If (key < T.key) Then
			T.left = insert(T.left, key)
		Else
			T.right = insert(T.right, key)
		End If
		// 插入节点完成后进行修正
		maintain(T, v≥T.key)
	End If
	Return T
为了简化删除操作，在SBT中若找不到要删除的值，我们就删除搜索到的最后一个结点，并且记录它。

同时在SBT的删除操作中，并不会马上对树进行调整，而是等待有新的节点加入时，才对树的结构进行修正。虽然这样会导致树暂时不满足SBT的性质，但在插入操作的影响下，树的高度仍然为O(log n*)，其中n*为插入的节点数量。

delete(T, key):
	s[T] = s[T] - 1
	If ((key == T.key) or (key < T.key and T.left is empty) or (key > T.key and T.right is empty)) Then
		ret = T.key
		If (T.left is empty or T.right is empty)
			// T只有一个儿子或没有儿子的情况
			If (T.left is not empty) Then
				T = T.left
			Else 
				T = T.right
			End If
		Else
			// 有两个儿子时，从子树中找一个节点来替换T
			// 由于T.key肯定是大于T.left中所有节点的
			// 因此会找到T.left中最大的值
			T.key = delete(T.left, T.key + 1)
		End If
	Else
		If (key < T.key) Then
			Return delete(T.left, key)
		Else
			Return delete(T.right, key)
		End If
	End If
	Return ret
*/