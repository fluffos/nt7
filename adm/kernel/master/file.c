// This program is a part of NT MudLIB

string creator_file(string str)
{
        return (string)call_other(SIMUL_EFUN_OB, "creator_file", str);
}

// 判断一个指定物件所属的区域
string domain_file(string str)
{
        return (string)call_other(SIMUL_EFUN_OB, "domain_file", str);
}

// 判断一个指定物件的作者为谁
// 需定义 PACKAGE_MUDLIB_STATS
string author_file(string str)
{
        return (string)call_other(SIMUL_EFUN_OB, "author_file", str);
}

// 为新创造的物件指定一个隐私字串
// 需定义 PRIVS
string privs_file(string filename)
{
        return filename;
}
