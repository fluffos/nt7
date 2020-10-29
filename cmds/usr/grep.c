// This program is a part of NITAN MudLIB

// grep.c 

inherit F_CLEAN_UP;

int help();
int do_grep(string,string,int);

nosave string pattern;
nosave string result;

string resolvePath(string path,int op)
{
        string *dn;
        string tmp;
        int i;
        if(path=="/")//对这个情况特殊处理
                return (op)?"/":"*";
        dn=explode(path,"/");
        if(op)//op为非0表示需要返回路径
        {
                //dn=dn-({dn[sizeof(dn)-1]});
                //tmp=implode(dn,"/")+"/";
                //上面的程序不好，不能对同名路径正确处理，比如不能在/log/log文件里搜索
                tmp="/";
                for(i=0;i<sizeof(dn)-1;i++)
                {
                        //write("合并"+dn[i]+"\n");
                        tmp+=dn[i]+"/";
                }
                return tmp;
        }
        else
                return dn[sizeof(dn)-1];
}

int main(object me, string arg)
{
        string  path,wild;
        int level;

        seteuid(getuid()); 

        if (!arg) return help();
        
        if( !wizardp(me) && time()-query_temp("last_grep", me)<30 )
                return notify_fail("系统气喘嘘地叹道：慢慢来 ....\n");   

        if (sscanf(arg,"%s %s",path,pattern)!=2)
                    return help();
            
            if (path != "help" && path != "news" && path != "all")
                    return help();
            
            set_temp("last_grep", time(), me);
        
        if (path == "news" || path == "all")
        {
                write("正在新闻系统中搜索，请稍后 ……\n");
                NEWS_D->do_search(me, "document " + pattern);
                if (path == "news")
                {
                        write("为节约系统资源，在30秒内只能进行搜索一次。\n");
                        return 1;
                }
                write("\n\n");
        }

            level=1;//带-d参数默认级别为所有级        
        path="/help";
        result="以下help帮助中包含你所要搜索的内容：\n";
        
        write("正在帮助系统中搜索，请稍后 ……\n");
        wild=resolvePath(path,0);
        path=resolvePath(path,1);

        do_grep(path,wild,level);
        write(result+"\n");
        write("为节约系统资源，在30秒内只能进行搜索一次。\n");
        return 1;
}

int do_grep(string path,string wild,int level)
{
        //int i;string *fs;
        string sbuffer,file;
        reset_eval_cost();//重新设置剩余执行时间，必须设置！
        if( query("env/debug", this_player()) )
                write("开始搜索"+path+wild+"\n");
        if(level<0)
        {
                //write("级别限制，不能再进入搜索。\n");
                return 0;
        }
        //for(i=0;i<(sizeof(fs=get_dir(path+wild))-1);i++)
        //        write(fs[i]+"\n");
        
        foreach(file in get_dir(path+wild))
        {
                //write("检查："+path+file+"\n");
                //write("file_size返回："+file_size(path+file)+"\n");
                if(file=="."||file=="..")
                        continue;
                
                switch(file_size(path+file))
                {
                        case -1:
                                //无法读取该目录，跳过
                                break;
                        case -2:
                                if(file!="."&&file!="..")
                                        do_grep(path+file+"/","*",level-1);
                                break;
                        default:
                                //write("检查文件："+path+file+"\n");
                                if(!sbuffer=read_file(path+file))
                                //对太大的文件读取可能要失败！而且不能试图读取二进制文件，因为含有\0!
                                {
                                        write("读文件"+path+file+"出错！\n");
                                        return 0;
                                }
                                if(strsrch(sbuffer,pattern)!=-1)
                                        result=result+file + "\n";//应该是记录下来，最后再输出 
                        /*
                                if(strsrch(read_file(path+file),pattern)!=-1)
                                        write(path+file+"\n");
                                break;
                        */
                }
                
        }
        return 1;
}

int help()
{
        write(@HELP
指令格式：grep <help/news/all> 查找内容

该指令功能相当强大，用于在相应地方或全局搜索指定查找的内容。

help:   在所有help文件中搜索。
news:   在所有的新闻中搜索。
all:    在所有help文件和新闻中搜索。
ex:
        grep help 华山派
ps:
        在所有的help文件中查找包含字符串“华山派”的相关文件。

HELP
    );
        return 1;
}