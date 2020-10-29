// /cmds/arch/findfile.c
// By Find.

inherit F_CLEAN_UP;

#define ITERS_PER_CALL        2

#define DATA_FILE        "/data/find.codes"
#define TMP_DATA_FILE        "/data/find.tmp"

mixed *stack;
string path;
int building_database = 0;
string *exclude = ({ "/data/","/www/", "/log/", "/backup/", "/temp/", "/dump/" });

string *split_path( string p )
{
        int pos;

        while(p[<1] == '/' && strlen(p) > 1) p = p[0..<2];
        pos = strsrch(p, '/', -1); /* find the last '/' */
        return ({ p[0..pos], p[pos+1..] });
}

string join_path( string dir, string file )
{
        if(dir[<1] != '/')
                return dir+"/"+file;
        return dir+file;
}

protected void end_building()
{
        cp(TMP_DATA_FILE,DATA_FILE);
        rm(TMP_DATA_FILE);
        write("Locate DB building is finished.\n");
        building_database = 0;
}

protected void do_building()
{
        int i = ITERS_PER_CALL;
        string *this_dir;

        while(i--)
        {
                string new_path;

                if(!sizeof(stack))
                {
                        end_building();
                        return;
                }

                if(intp(stack[0]))
                {
                        stack = stack[1..];
                        path = split_path(path)[0];
                        i++;
                        continue;
                }

                new_path = path + stack[0]+"/";
                stack = stack[1..];
                if(sizeof(exclude) && (member_array(new_path,exclude) != -1))
                        continue;

                this_dir = get_dir(new_path+"*",-1);
                if(arrayp(this_dir))
                        this_dir = this_dir[2..];
                else
                        continue;

                /* prepend the dir and write into the file */
                map(this_dir,(:write_file(TMP_DATA_FILE,
                        join_path($(new_path),$1[0])+"\n"):));

                /* filter out just the dirs and extract the names */
                this_dir = map(filter(this_dir, (:$1[1] == -2:)), (:$1[0]:));

                /* push onto stack w/ a sentinel to go up the dir tree */
                if(sizeof(this_dir))
                {
                        stack = this_dir + ({0}) + stack;
                        path = new_path;
                }
        }
        call_out((:do_building:), 2);
}

protected void begin_database_build()
{
        stack = ({""});
        path = "";

        if(file_size(TMP_DATA_FILE) != -1)
                rm(TMP_DATA_FILE);
        do_building();
        building_database = 1;
}

nomask int main(object me,string arg) 
{
        string find,subfind;
        string *outstr = ({}),*content;
        int i,flag=0,p;

        if (! SECURITY_D->valid_grant(me, "(admin)")) 
                return 0; 

        if( objectp(me) && (!arg || arg == "") )
                return notify_fail( "指令格式：: findfile <string>\n");

        if( (arg == "-u") || !objectp(me) )
        {
                if(building_database)
                        return notify_fail("Already building database,please wait a while.\n");

                if(!objectp(me))
                {
                        if(!previous_object() || (geteuid(previous_object()) != ROOT_UID) )
                                return 0;
                }

                else if(wiz_level(me) < wiz_level("(arch)"))
                        return notify_fail("只有(arch)以上的巫师才能执行此功能\n");

                write("Building database... This will takes a while.\n");
                log_file("updatedb",sprintf("findfile database been updated by %s at %s\n",
                        objectp(me)&&userp(me)?capitalize(geteuid(me)):"system",ctime(time())));
                begin_database_build();
                return 1;
        }

        else
        {
                if(file_size(DATA_FILE) <= 0)
                        return notify_fail("请先使用 'findfile -u' 命令建立索引库。\n");
                if(strsrch(arg,"*") >= 0)
                {
                        if(strsrch(arg,"*") != strsrch(arg,"*",-1))
                                return notify_fail("只能使用一个通配符 '*'。\n");
                        if(strsrch(arg,"*") == 0)
                        {
                                sscanf(arg,"*%s",find);
                                flag = 1;
                        }
                        else if(strsrch(arg,"*") == (strlen(arg)-1))
                        {
                                sscanf(arg,"%s*",find);
                                flag = 2;
                        }
                        else
                        {
                                sscanf(arg,"%s*%s",find,subfind);
                                flag = 3;
                        }
                }
                else
                        find = arg;

                content = explode(read_file(DATA_FILE),"\n");
                for(i=0;i<sizeof(content);i++)
                {
                        if( (p = strsrch(content[i],find)) < 0)
                                continue;

                        switch (flag)
                        {
                                case 0:
                                        outstr += ({ content[i] });
                                        break;
                                case 1:
                                        if( (p + strlen(find)) == strlen(content[i]) )
                                        outstr += ({ content[i] });
                                        break;
                                case 2:
                                        if(p == 0)
                                        outstr += ({ content[i] });
                                        break;
                                case 3:
                                        if( (p == 0)
                                        && ((p = strsrch(content[i],subfind)) >  0)
                                        && ((p + strlen(subfind)) == strlen(content[i])) )
                                        outstr += ({ content[i] });
                                        break;
                        }
                }

                if(!sizeof(outstr))
                        return notify_fail("没有发现与 "+arg+" 匹配的文件名.\n");

                else
                        me->start_more(implode(outstr,"\n")+"\n");

                return 1;
        }
}

int clean_up()
{
        if(building_database)
                return 1;
        else
                return ::clean_up();
}

int help(object me)
{
        if(!wizardp(me))
                return 0;
write(@HELP
指令格式：: findfile <string>

        按文件名查找文件，可以使用通配符 '*'。

        如:
                findfile *.bak
                findfile /adm/etc/wiz*
                findfile /cmds/*promote.c

HELP
    );
    return 1;
}
