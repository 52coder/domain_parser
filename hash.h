#ifndef __HASH_H__
#define __HASH_H__

struct hash_node_st {
	void *key;
	int klen;					/* key and len */
	unsigned int __hval;		/* hash value of this node, for rehashing */
	void *val;					/* value */
	struct hash_node_st *next;
};

/**
 * �ͷŹ�ϣ����data�ֶεĺ�������
 * �ͷź�����Ӧ�öԵ�ǰhash������ɾ�������������ֲ���Ҫ������
 * \param data ����ָ��
 */
typedef void (*hash_data_free_func_t)(void *data);

/** 
 * ��ϣ��������
 * \param key ��ϣ���key
 * \param klen key�ĳ���
 */
typedef unsigned int (*hash_key_func_t)(const void *key, int klen);

/**
 * ��ϣ��ṹ
 */
typedef struct hash_st {
	struct hash_node_st **slots;
	unsigned int nslot;			/* number of bucket */
	unsigned int max_element;	/* max element allowed for next rehashing */
	unsigned int nelement;		/* hash entry count */
	hash_data_free_func_t hdel;
	hash_key_func_t hkey;
} hash_st;

/**
 * ȡ�ù�ϣ������
 */
#define hash_count(ha)	((ha)->nelement)

/**
 * ����һ����ϣ��
 * ʹ��hash_destroy�ͷŴ����Ĺ�ϣ��
 * \param del �ͷ�data�Ļص�������data�ͷŽ��ڹ�ϣ�����ٻ�key���滻ʱִ�У�����Ϊ�գ�Ĭ�ϲ��ͷţ�
 * \param keyf ʹ���Զ���Ĺ�ϣ����������Ϊ�գ�Ĭ��ʹ��time33���ֽڽ��м��㣩
 * \retval NULL ����ʧ��
 * \retval !NULL ��ϣ��ṹָ��
 */
hash_st *hash_create(hash_data_free_func_t del, hash_key_func_t keyf);

/**
 * ��ϣ�����
 * \note ��������key���ڣ��µ�val���滻�Ѵ��ڵ����ݣ����滻�����ݽ����ù�ϣ��data�ͷŻص������ͷ�
 * \param ht ��ϣ��ṹ
 * \param key key�ֶ�
 * \param klen key�ĳ���
 * \param val ���������
 */
void hash_insert(hash_st *ht, const void *key, int klen, void *val);

/**
 * ��ϣ�����
 * \param ht ��ϣ��ṹ
 * \param key key�ֶ�
 * \param klen key�ĳ���
 * \param [out] val ��������ָ��
 * \retval 0 �ɹ�����
 * \retval !0 �޷��ҵ�
 */
int hash_search(hash_st *ht, const void *key, int klen, void **val);

/**
 * ��ϣ��ɾ����
 * \note ɾ�������ݽ�����data�ͷŻص������ͷ�
 * \param ht ��ϣ��ṹ
 * \param key key�ֶ�
 * \param len key�ĳ���
 * \retval 0 �ɹ�ɾ��
 * \retval !0 �޷��ҵ���ֵ
 */
int hash_delete(hash_st *ht, const void *key, int len);

/**
 * ��ϣ���ͷ�
 * \note �������ݽ�����data�ͷŻص������ͷ�
 * \param ht ��ϣ��ṹ
 */
void hash_destroy(hash_st *ht);

/**
 * ��ϣ������������ͣ�����ʱ����ÿ��key-value�ϵ��øú���
 * \param key �����ֶ�
 * \param klen �����ֶγ���
 * \param val ֵָ��
 * \param data �Զ�������
 * \return �������뷵��0���������������������ظ�ֵ
 */
typedef int (*hash_walk_func_t)(const void *key, int klen, void *val, void *data);

/**
 * ��ϣ������������еļ�ֵ�Ե���fn�ص�
 * \param ht ��ϣ��ṹ
 * \param data �û��ص�����
 * \param fn ��ÿ����ֵ�Ե��øûص�������ص����ط�0ֵ��������������������ֵ����
 * \retval 0 �ɹ����б�������
 * \retval !0 �ص������˷�0ֵ
 */
int hash_walk(hash_st *ht, void *data, hash_walk_func_t fn);

#endif
