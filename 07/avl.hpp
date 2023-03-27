#pragma once

#include <iterator>
#include <limits>
#include <stdexcept>
#include <list>
#include <tuple>
#include "avl_tree_node.hpp"


	template <typename T>
	class allocator
	{
	public:
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using const_pointer = const T*;
		using reference = typename std::add_lvalue_reference<T>::type;
		using const_reference = typename std::add_lvalue_reference<const T>::type;
		using value_type = T;

		allocator() noexcept = default;

		allocator(const allocator&) noexcept = default;

		template <class U>
		explicit allocator(const allocator<U>&) noexcept;

		~allocator() = default;

		pointer allocate(size_type n)
		{
			void* p = ::operator new(n * sizeof(value_type));
			return static_cast<pointer>(p);
		}

		void deallocate(pointer p, size_type n) noexcept
		{
			::operator delete(p);
		}
	};

	template <typename ValueType, typename Node>
	class avl_tree_iterator
	{
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = ValueType;
		using difference_type = std::ptrdiff_t;
		using reference = ValueType&;
		using pointer = ValueType*;

		template <typename V, typename N>
		friend class avl_tree_const_iterator;

		template <typename K, typename T,
		          class Compare,
		          typename Alloc>
		friend class avl_tree;

		avl_tree_iterator() noexcept = default;

		avl_tree_iterator(Node* node) : node_(node)
		{
			node_->increment_ref_count();
		}

		avl_tree_iterator(const avl_tree_iterator& other) noexcept : avl_tree_iterator(other.node_)
		{
		}

		~avl_tree_iterator()
		{
			node_->decrement_ref_count();
		}

		reference operator*() const
		{
			return node_->get_ref();
		}

		pointer operator->() const
		{
			return node_->get_pointer();
		}

		avl_tree_iterator& operator++()
		{
			node_->decrement_ref_count();

			if (node_->is_deleted())
			{
				node_ = node_->get_next();
			}
			else
			{
				if (node_->get_right() != nullptr)
				{
					node_ = node_->get_right();
					while (node_->get_left() != nullptr)
						node_ = node_->get_left();
				}
				else
				{
					Node* tmp;
					while (node_->get_parent() != nullptr)
					{
						tmp = node_;
						node_ = node_->get_parent();
						if (tmp == node_->get_left())
							break;
					}
				}
			}

			node_->increment_ref_count();
			return *this;
		}

		avl_tree_iterator operator++(int)
		{
			auto tmp = avl_tree_iterator(*this);
			operator++();
			return tmp;
		}

		avl_tree_iterator& operator--()
		{
			node_->decrement_ref_count();

			if (node_->is_deleted())
			{
				node_ = node_->get_next();
			}
			else
			{
				if (node_->get_left() != nullptr)
				{
					node_ = node_->get_left();
					while (node_->get_right() != nullptr)
						node_ = node_->get_right();
				}
				else
				{
					Node* tmp;
					while (node_->get_parent() != nullptr)
					{
						tmp = node_;
						node_ = node_->get_parent();
						if (tmp == node_->get_right())
							break;
					}
				}
			}

			node_->increment_ref_count();
			return *this;
		}

		avl_tree_iterator operator--(int)
		{
			auto tmp = avl_tree_iterator(*this);
			operator--();
			return tmp;
		}

		friend bool operator==(const avl_tree_iterator<ValueType, Node>& a, const avl_tree_iterator<ValueType, Node>& b)
		{
			return a.node_ == b.node_;
		}

		friend bool operator!=(const avl_tree_iterator<ValueType, Node>& a, const avl_tree_iterator<ValueType, Node>& b)
		{
			return !(a == b);
		}

	private:
		Node* node_;
	};

	template <typename ValueType, typename Node>
	class avl_tree_const_iterator
	{
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = ValueType;
		using difference_type = std::ptrdiff_t;
		using reference = const ValueType&;
		using pointer = const ValueType*;

		template <typename K, typename T,
		          class Compare,
		          typename Alloc>
		friend class avl_tree;

		avl_tree_const_iterator() noexcept = default;

		avl_tree_const_iterator(const avl_tree_iterator<ValueType, Node>& other) noexcept : node_(other.node_)
		{
			node_->increment_ref_count();
		}

		avl_tree_const_iterator(const avl_tree_const_iterator& other) noexcept : avl_tree_const_iterator(other.node_)
		{
		}

		~avl_tree_const_iterator()
		{
			node_->decrement_ref_count();
		}

		reference operator*() const
		{
			return node_->get_ref();
		}

		pointer operator->() const
		{
			return node_->get_pointer();
		}

		avl_tree_const_iterator& operator++()
		{
			node_->decrement_ref_count();

			if (node_->is_deleted())
			{
				node_ = node_->get_next();
			}
			else
			{
				if (node_->get_right() != nullptr)
				{
					node_ = node_->get_right();
					while (node_->get_left() != nullptr)
						node_ = node_->get_left();
				}
				else
				{
					Node* tmp;
					while (node_->get_parent() != nullptr)
					{
						tmp = node_;
						node_ = node_->get_parent();
						if (tmp == node_->get_left())
							break;
					}
				}
			}

			node_->increment_ref_count();
			return *this;
		}

		avl_tree_const_iterator operator++(int)
		{
			auto tmp = avl_tree_const_iterator(*this);
			operator++();
			return tmp;
		}

		avl_tree_const_iterator& operator--()
		{
			node_->decrement_ref_count();

			if (node_->is_deleted())
			{
				node_ = node_->get_next();
			}
			else
			{
				if (node_->get_left() != nullptr)
				{
					node_ = node_->get_left();
					while (node_->get_right() != nullptr)
						node_ = node_->get_right();
				}
				else
				{
					Node* tmp;
					while (node_->get_parent() != nullptr)
					{
						tmp = node_;
						node_ = node_->get_parent();
						if (tmp == node_->get_right())
							break;
					}
				}
			}

			node_->increment_ref_count();
			return *this;
		}

		avl_tree_const_iterator operator--(int)
		{
			auto tmp = avl_tree_const_iterator(*this);
			operator--();
			return tmp;
		}

		friend bool operator==(const avl_tree_const_iterator<ValueType, Node>& a,
		                       const avl_tree_const_iterator<ValueType, Node>& b)
		{
			return a.node_ == b.node_;
		}

		friend bool operator!=(const avl_tree_const_iterator<ValueType, Node>& a,
		                       const avl_tree_const_iterator<ValueType, Node>& b)
		{
			return !(a == b);
		}

	private:
		Node* node_;
	};

	template <
		typename K, typename T,
		class Compare = std::less<K>,
		typename Alloc = std::allocator<avl_tree_node<const K, T>>>
	class avl_tree
	{
	public:
		using key_type = K;
		using mapped_type = T;
		using key_compare = Compare;
		using allocator_type = Alloc;
		using value_type = std::pair<const key_type, mapped_type>;
		using reference = value_type&;
		using const_reference = const value_type&;
		using node_type = avl_tree_node<const key_type, mapped_type>;
		using iterator = avl_tree_iterator<value_type, node_type>;
		using const_iterator = avl_tree_const_iterator<value_type, node_type>;
		using revers_iterator = std::reverse_iterator<iterator>;
		using const_revers_iterator = std::reverse_iterator<const_iterator>;
		using size_type = std::size_t;

		avl_tree() : root_(nullptr), min_node_(nullptr), max_node_(nullptr), right_border_(new node_type()),
		             size_(0), allocator_(allocator_type()), key_compare_(key_compare()),
		             deleted_nodes_(std::list<node_type*>())
		{
		}

		avl_tree(const avl_tree& tree) : avl_tree(tree.get_allocator())
		{
			insert(tree.begin(), tree.end());
		}

		avl_tree(avl_tree&& tree) : avl_tree(tree)
		{
		}

		explicit avl_tree(const allocator_type& a) : avl_tree()
		{
			allocator_ = a;
		}

		avl_tree(const avl_tree& tree,
		         const allocator_type& a) : avl_tree(a)
		{
			insert(tree.begin(), tree.end());
		}

		avl_tree(avl_tree&& tree,
		         const allocator_type& a) : avl_tree(tree, a)
		{
		}

		template <typename InputIterator>
		avl_tree(InputIterator first, InputIterator last) : avl_tree()
		{
			insert(first, last);
		}

		avl_tree(std::initializer_list<value_type> l) : avl_tree()
		{
			insert(l);
		}

		~avl_tree()
		{
			clear();
			delete right_border_;
		}

		avl_tree& operator=(const avl_tree& tree)
		{
			auto tmp(tree);
			swap(tmp);
			return *this;
		}

		avl_tree& operator=(avl_tree&& tree)
		{
			swap(tree);
			return *this;
		}

		avl_tree& operator=(std::initializer_list<value_type> l)
		{
			avl_tree tmp(l);
			swap(tmp);
			return *this;
		}

		std::pair<iterator, bool> insert(const value_type& x)
		{
			return common_insert(value_type(x));
		}

		std::pair<iterator, bool> insert(value_type&& x)
		{
			return common_insert(std::move(x));
		}

		template <typename _InputIterator>
		void insert(_InputIterator first, _InputIterator last)
		{
			auto i = first;
			for (; i != last; ++i)
			{
				insert(*i);
			}
		}

		void insert(std::initializer_list<value_type> l)
		{
			insert(l.begin(), l.end());
		}

		template <typename _Obj>
		std::pair<iterator, bool> insert_or_assign(const key_type& k, _Obj&& obj)
		{
			return common_insert_or_assign<_Obj>(key_type(k), std::forward<_Obj>(obj));
		}

		template <typename _Obj>
		std::pair<iterator, bool> insert_or_assign(key_type&& k, _Obj&& obj)
		{
			return common_insert_or_assign<_Obj>(std::move(k), std::forward<_Obj>(obj));
		}

		template <typename... _Args>
		std::pair<iterator, bool> emplace(_Args&&... args)
		{
			return insert(value_type(std::forward<_Args>(args)...));
		}

		template <typename... _Args>
		std::pair<iterator, bool> try_emplace(const key_type& k, _Args&&... args)
		{
			return common_try_emplace(std::move(key_type(k)), std::move(args)...);
		}

		template <typename... _Args>
		std::pair<iterator, bool> try_emplace(key_type&& k, _Args&&... args)
		{
			return common_try_emplace(std::move(k), std::move(args)...);
		}

		iterator erase(const_iterator position)
		{
			return common_erase(position);
		}

		iterator erase(iterator position)
		{
			return common_erase(position);
		}

		size_type erase(const key_type& x)
		{
			auto i = find(x);

			if (i == end())
				return 0;
			erase(i);
			return 1;
		}

		iterator erase(const_iterator first, const_iterator last)
		{
			auto i = first;

			for (; i != last;)
			{
				i = erase(i);
			}

			return iterator(i.node_);
		}

		template <typename _P2>
		void merge(avl_tree<K, T, _P2, Alloc>& source)
		{
			for (auto i = source.cbegin(); i != source.cend();)
			{
				auto tmp = insert(*i);
				if (tmp.second == true)
				{
					i = source.erase(i);
				}
				else
				{
					++i;
				}
			}
		}

		template <typename _P2>
		void merge(avl_tree<K, T, _P2, Alloc>&& source)
		{
			insert(source.cbegin(), source.cend());
		}

		void clear() noexcept
		{
			erase(begin(), end());
		}

		void swap(avl_tree& x)
		{
			std::swap(root_, x.root_);
			std::swap(min_node_, x.min_node_);
			std::swap(max_node_, x.max_node_);
			std::swap(right_border_, x.right_border_);
			std::swap(size_, x.size_);
			std::swap(allocator_, x.allocator_);
			std::swap(key_compare_, x.key_compare_);
			deleted_nodes_.swap(x.deleted_nodes_);
		}

		mapped_type& operator[](const key_type& k)
		{
			auto res = insert(value_type{k, mapped_type()});
			return res.first->second;
		}

		mapped_type& operator[](key_type&& k)
		{
			auto res = insert(value_type{std::move(k), mapped_type()});
			return res.first->second;
		}

		mapped_type& at(const key_type& k)
		{
			return common_at(k);
		}

		const mapped_type& at(const key_type& k) const
		{
			return common_at(k);
		}

		iterator begin() noexcept
		{
			if (min_node_ == nullptr)
			{
				return iterator(right_border_);
			}
			return iterator(min_node_);
		}

		iterator end() noexcept
		{
			return iterator(right_border_);
		}

		const_iterator begin() const noexcept
		{
			return cbegin();
		}

		const_iterator end() const noexcept
		{
			return cend();
		}

		const_iterator cbegin() const noexcept
		{
			if (min_node_ == nullptr)
			{
				return const_iterator(right_border_);
			}
			return const_iterator(min_node_);
		}

		const_iterator cend() const noexcept
		{
			return const_iterator(right_border_);
		}

		revers_iterator rbegin() noexcept
		{
			return revers_iterator(iterator(right_border_));
		}

		revers_iterator rend() noexcept
		{
			if (min_node_ == nullptr)
			{
				return revers_iterator(iterator(right_border_));
			}
			return revers_iterator(iterator(min_node_));
		}

		const_revers_iterator rbegin() const noexcept
		{
			return crbegin();
		}

		const_revers_iterator rend() const noexcept
		{
			return crend();
		}

		const_revers_iterator crbegin() const noexcept
		{
			return const_revers_iterator(iterator(right_border_));
		}

		const_revers_iterator crend() const noexcept
		{
			if (min_node_ == nullptr)
			{
				return const_revers_iterator(iterator(right_border_));
			}
			return const_revers_iterator(iterator(min_node_));
		}

		const_iterator find(const key_type& x) const
		{
			auto node = common_find(x);

			if (node == nullptr)
			{
				return cend();
			}
			return const_iterator(node);
		}

		iterator find(const key_type& x)
		{
			auto node = common_find(x);

			if (node == nullptr)
			{
				return end();
			}
			return iterator(node);
		}

		bool contains(const key_type& x) const
		{
			if (find(x) == cend())
				return false;
			return true;
		}

		bool empty() const noexcept
		{
			return begin() == end();
		}

		size_type size() const noexcept
		{
			return size_;
		}

		size_type max_size() const noexcept
		{
			return std::numeric_limits<size_type>().max();
		}

		allocator_type get_allocator() const noexcept
		{
			return allocator_;
		}

		bool operator==(const avl_tree& other) const
		{
			if (other.size() != size_)
			{
				return false;
			}

			auto i = cbegin();
			auto j = other.cbegin();

			while (i != cend())
			{
				if ((*i).first != (*j).first)
					return false;
				if ((*i).second != (*j).second)
					return false;
				++i;
				++j;
			}

			return true;
		}

		size_type get_height()
		{
			return root_->get_height();
		}

	private:
		node_type* root_;
		node_type* min_node_;
		node_type* max_node_;
		node_type* right_border_;
		size_type size_;
		allocator_type allocator_;
		key_compare key_compare_;
		std::list<node_type*> deleted_nodes_;

		std::pair<iterator, bool> common_insert(const value_type& x)
		{
			auto iter = find(x.first);
			if (iter != end())
			{
				return std::pair<iterator, bool>(iter, false);
			}

			disconnect_border();
			auto node = allocator_.allocate(1);
			new(node) node_type{node_type(x)};
			insert_node_to_tree(node);
			rebalance(node);

			root_->set_parent(nullptr);

			size_++;
			update_min_max_nodes();
			connect_border();

			return std::pair<iterator, bool>(iterator(node), true);
		}

		iterator common_erase(const_iterator position)
		{
			disconnect_border();
			auto [next, to_rebalance] = erase_node_from_tree(position.node_);
			rebalance(to_rebalance);

			if (root_ != nullptr)
				root_->set_parent(nullptr);

			size_--;
			update_min_max_nodes();
			connect_border();
			return iterator(next);
		}

		mapped_type& common_at(const key_type& k)
		{
			iterator iter = find(k);
			if (iter == end())
			{
				throw std::out_of_range("Item not found.");
			}
			return (iter->second);
		}

		template <typename... _Args>
		std::pair<iterator, bool> common_try_emplace(key_type&& k, _Args&&... args)
		{
			auto iter = find(k);
			if (iter != end()) return std::make_pair(iter, false);

			return emplace(std::piecewise_construct,
			               std::forward_as_tuple(std::move(k)),
			               std::forward_as_tuple(std::forward<_Args>(args)...));
		}

		node_type* common_find(const key_type& x) const
		{
			disconnect_border();
			auto node = root_;
			while (node != nullptr && node->get_key() != x)
			{
				if (x < node->get_key())
				{
					node = node->get_left();
				}
				else
				{
					node = node->get_right();
				}
			}
			connect_border();
			return node;
		}

		template <typename _Obj>
		std::pair<iterator, bool> common_insert_or_assign(key_type&& k, _Obj&& obj)
		{
			auto res = insert(value_type{std::move(k), obj});
			if (res.second == false)
			{
				res.first->second = std::forward<_Obj>(obj);
			}
			return res;
		}

		void insert_node_to_tree(node_type* node)
		{
			auto parent = root_;

			if (parent == nullptr)
				root_ = node;

			while (parent != nullptr)
			{
				if (node->get_key() < parent->get_key())
				{
					if (parent->get_left() == nullptr)
					{
						parent->set_left(node);
						break;
					}
					else
					{
						parent = parent->get_left();
					}
				}
				else if (node->get_key() > parent->get_key())
				{
					if (parent->get_right() == nullptr)
					{
						parent->set_right(node);
						break;
					}
					else
					{
						parent = parent->get_right();
					}
				}
			}
		}

		std::tuple<node_type*, node_type*> erase_node_from_tree(node_type* node)
		{
			auto to_delete = node;
			node_type* to_replace = nullptr;
			node_type* to_replace_child = nullptr;
			node_type* to_rebalance = nullptr;
			node_type* next = nullptr;

			if (node == max_node_)
			{
				next = right_border_;
			}
			else
			{
				auto to_next_iterator = ++iterator(node);
				next = to_next_iterator.node_;
			}

			if (to_delete->get_left() == nullptr && to_delete->get_right() == nullptr && node->get_parent() == nullptr)
			{
				root_ = nullptr;
				to_rebalance = nullptr;
			}
			else
			{
				if (to_delete->get_left() != nullptr || to_delete->get_right() != nullptr)
				{
					auto to_replace_iterator = iterator(node);

					if (to_delete->get_left() != nullptr)
					{
						--to_replace_iterator;

						while (to_replace_iterator.node_->get_right() != nullptr)
						{
							++to_replace_iterator;
						}

						to_replace_child = to_replace_iterator.node_->get_left();
					}
					else
					{
						++to_replace_iterator;

						while (to_replace_iterator.node_->get_left() != nullptr)
						{
							--to_replace_iterator;
						}

						to_replace_child = to_replace_iterator.node_->get_right();
					}

					to_replace = to_replace_iterator.node_;
					auto to_replace_parent = to_replace->get_parent();

					if (to_replace_parent != nullptr)
					{
						if (to_replace_parent->get_left() == to_replace)
							to_replace_parent->set_left(to_replace_child);
						else
							to_replace_parent->set_right(to_replace_child);
					}

					to_replace->set_left(to_delete->get_left());
					to_replace->set_right(to_delete->get_right());
					to_replace->set_parent(to_delete->get_parent());

					to_rebalance = to_replace;
				}

				auto to_delete_parent = node->get_parent();

				if (to_delete_parent != nullptr)
				{
					if (to_delete_parent->get_left() == to_delete)
						to_delete_parent->set_left(to_replace);
					else
						to_delete_parent->set_right(to_replace);

					if (to_delete->get_left() == nullptr && to_delete->get_right() == nullptr)
						to_rebalance = to_delete_parent;
				}
			}

			to_delete->set_left(nullptr);
			to_delete->set_right(nullptr);
			to_delete->set_parent(nullptr);
			to_delete->set_next(next);
			to_delete->set_deleted(true);
			deleted_nodes_.push_back(to_delete);

			return std::make_tuple(next, to_rebalance);
		}

		void rebalance(node_type* start_node)
		{
			auto node = start_node;

			while (node != nullptr)
			{
				int balance = node->get_balance();
				auto parent = node->get_parent();

				auto result = node;
				if (balance > 1 && node->get_left()->get_balance() > 0)
					result = small_right_rotate(node);

				else if (balance > 1 && node->get_left()->get_balance() <= 0)
					result = big_right_rotate(node);

				else if (balance < -1 && node->get_right()->get_balance() < 0)
					result = small_left_rotate(node);

				else if (balance < -1 && node->get_right()->get_balance() >= 0)
					result = big_left_rotate(node);

				if (parent == nullptr)
				{
					root_ = result;
				}
				else
				{
					if (parent->get_left() == node)
					{
						parent->set_left(result);
					}
					else
					{
						parent->set_right(result);
					}
				}

				node = parent;
			}
		}

		node_type* small_left_rotate(node_type* node)
		{
			auto right = node->get_right();

			node->set_right(right->get_left());
			right->set_left(node);

			return right;
		}

		node_type* small_right_rotate(node_type* node)
		{
			auto left = node->get_left();

			node->set_left(left->get_right());
			left->set_right(node);

			return left;
		}

		node_type* big_left_rotate(node_type* node)
		{
			node->set_right(small_right_rotate(node->get_right()));
			return small_left_rotate(node);
		}

		node_type* big_right_rotate(node_type* node)
		{
			node->set_left(small_left_rotate(node->get_left()));
			return small_right_rotate(node);
		}

		void update_min_max_nodes()
		{
			if (root_ == nullptr)
			{
				max_node_ = nullptr;
				min_node_ = nullptr;
				return;
			}

			max_node_ = root_;
			min_node_ = root_;

			while (max_node_->get_right() != nullptr)
			{
				max_node_ = max_node_->get_right();
			}

			while (min_node_->get_left() != nullptr)
			{
				min_node_ = min_node_->get_left();
			}
		}

		void connect_border() const
		{
			if (size_ > 0)
			{
				max_node_->set_right(right_border_);
			}
		}

		void disconnect_border() const
		{
			if (size_ > 0)
			{
				max_node_->set_right(nullptr);
			}
		}
	};
