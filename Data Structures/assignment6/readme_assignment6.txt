hw6_1번.cpp
Visual Studio 2019(Windows10)

1. void build_max_heap(HeapType* h)
-input: we will build maxheap in h
-int parent: index of current node
-int child: index of child node
-element temp: data in i th heap

-> walk backwards through the array from n/2 to 1, moving the element on each node until it meets the heap property
(elements in index n/2+1 to n already met the heap property )
->implement like delete_max_heap function

2. measure running time
: use clock() function
-double start: time when 'heap_sort' function is started
-double finish: time when 'heap_sort' function is finished
-double duration: duration time of 'heap_sort'

->print the runtime
printf("Input size is %d, and the runtime is %.50f seconds\n",input_size, duration);


3. other functions
: same with the skeleton code



hw6_2.cpp
Visual Studio 2019(Windows10)

1. void huffman_traversal(TreeNode* node)
-input(TreeNode* node): root node
-int index: index of node in huffman tree
-int code[MAX_BIT]: huffman code
-int size: number of bits
-int row: the row index of m_LUT

-> generate huffman code and save them in m_LUT 
-> save number of bits of each huffman code in m_nit_size

2. void huffman_encoding(char* str, bits_stream* bits_str)
-char* str: data we will encode
-bits_stream* bits_str: save encoded string
-int interval: length of bits_str
-int idx= 0: index of bits_str

->print encoded string and totall length of bits stream

3. int huffman_decoding(bits_stream* bits_str, TreeNode* node, char* decoded_str)
-bits_stream* bits_str: we will decoded bits_str->stream
-TreeNode* node: root node of huffman tree
-char* decoded_str: save decoded string 
-TreeNode* parent: current node
-TreeNode* child: child node of current node
-int index_char: total number of decoded chars & index of decoded_str

-> print decoded string and total number of decoded characters

4. other functions
:same with the skeleton code