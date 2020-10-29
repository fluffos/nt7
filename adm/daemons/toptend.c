//JackyBoy Write these Functions for CCTX's TOPTEN!
//Updated in 1999/3/8

#include <ansi.h>
#include <mudlib.h>

#define MAX_LEAVE_TOP 10

#define TOPTEN_JINGLI      DATA_DIR + "topten/jingli.txt"
#define TOPTEN_DUSHU       DATA_DIR + "topten/dushu.txt"
#define TOPTEN_RICH        DATA_DIR + "topten/rich.txt"
#define TOPTEN_EXP         DATA_DIR + "topten/exp.txt"
#define TOPTEN_NEILI       DATA_DIR + "topten/neili.txt"
#define DUSHU_B                 NOR+WHT"江湖"HIR"读书"NOR+WHT"排行榜"NOR
#define JINGLI_B                 NOR+RED"江湖"HIW"精力"NOR+RED"排行榜"NOR
#define RICH_B                     NOR+CYN"江湖"HIY"富豪"NOR+CYN"排行榜"NOR
//#define PKER_B                 CYN"十大"HIR"杀人狂魔"NOR
#define EXP_B           NOR+YEL"江湖"HIM"经验"NOR+YEL"排行榜"NOR
//#define SHEN_B        CYN"十大"RED"邪道人物"NOR               
#define NEILI_B                    NOR+BLU"江湖"HIC"内力"NOR+BLU"排行榜"NOR
//#define PER_B                    CYN"江湖"HIM"十大美女"NOR
//#define AGE_B                    CYN"江湖十大"GRN"老前辈"NOR

void topten_checkplayer(object);
int get_all_data(object,string);
int topten_del(string,string);
int topten_add(object,string);
int topten_save(string,string,string);
string topten_query(string);
string query_type();


void topten_checkplayer(object player)
{//对于外貌等属性用先天还是后天呢？还有有些是需要有点区分的（比如男女性别）
        topten_add(player,"rich");
        //topten_add(player,"pker");
        topten_add(player,"exp");
        //topten_add(player,"shen");
        topten_add(player,"neili");
        //topten_add(player,"per");        
        //topten_add(player,"age");
        topten_add(player,"jingli");
        topten_add(player,"dushu");
        return;
}

string query_type()
{
        return HIY+CHINESE_MUD_NAME+"现在有以下类型的排行榜：\n"+
                HIR"一：\t"NOR+RICH_B+"\n"+
                HIR"二：\t"NOR EXP_B+"\n"+
                //HIR"三：\t"NOR+PKER_B+"\n"+
                HIR"三：\t"NOR+NEILI_B+"\n"+
                HIR"四：\t"NOR+JINGLI_B+"\n"+
                HIR"五：\t"NOR+DUSHU_B+"\n"+
                //HIR"五：\t"NOR+SHEN_B+"\n"+
                //HIR"六：\t"NOR+PER_B+"\n"+
                //HIR"七：\t"NOR+AGE_B+"\n"+
                NOR;
}
int topten_save(string f_name,string b_name,string str)
{
        string *astr;
        int i;

        astr=explode(str,"\n");

        str="";
        for(i=0;i<sizeof(astr)&&i<MAX_LEAVE_TOP;i++)
                str+=astr[i]+"\n";

        if(!write_file(f_name,str,1))
                return notify_fail("无法写文件"+f_name+"，权限不够!不能更新"+b_name+"!\n");

        return 1;
}

string topten_query(string type)
{
        string b_name,f_name,str,*astr,*bstr,name,id;
        int i,j,data;
        switch(type)
        {
                case "rich":
                        b_name=RICH_B;
                        f_name=TOPTEN_RICH;
                        break;
                /*case "pker":
                        b_name=PKER_B;
                        f_name=TOPTEN_PKER;
                        break;*/
                case "exp":
                        b_name=EXP_B;
                        f_name=TOPTEN_EXP;
                        break;
                /*case "shen":
                        b_name=SHEN_B;
                        f_name=TOPTEN_SHEN;
                        break;*/
                case "neili":
                        b_name=NEILI_B;
                        f_name=TOPTEN_NEILI;
                        break;
                case "jingli":
                        b_name=JINGLI_B;
                        f_name=TOPTEN_JINGLI;
                        break;
                case "dushu":
                        b_name=DUSHU_B;
                        f_name=TOPTEN_DUSHU;
                        break;
                default:
                        return query_type();
        }
        if(file_size(f_name)==-1)
                return b_name+"的数据文件还没有创建！\n";
        astr=explode(read_file(f_name),"\n");
        str=HIG+CHINESE_MUD_NAME+" : "NOR+b_name+"\n";
        for(i=0;i<sizeof(astr);i++)
        {
                bstr=explode(astr[i],";");
                str+=NOR CYN"排行第"HIR+chinese_number(i+1)+NOR"：";
                for(j=0;j<sizeof(bstr);j++)
                {
                        if(sscanf(bstr[j],"%s(%s)%d",name,id,data)!=3)
                                return "数据错误!文件："+f_name+"第"+i+"行第"+j+"项！\n"+
                                        "该行数据："+bstr[j]+"\n";
                        str+=name+"("+id+")\t";
                }
                str+="\n"NOR;
        }
        return str;
}
int get_all_data(object player,string type)
{
        int total;
        
        switch(type)
        {
                case "rich":
                        total=MONEY_D->player_carry(player); 
                        break;
                /*case "pker":
                        total=query("combat/PKS", player);
                        break;*/
                case "exp":
                        total=query("combat_exp", player);
                        break;
                case "dushu":
                        total=(int)player->query_skill("literate",1);
                        break;
                case "neili":
                        total=query("max_neili", player);
                        break;
                case "jingli":
                        total=query("max_jingli", player);
                        break;
                /*case "per":
                        if( query("gender", player) != "女性" )
                        total=-1;
                else
                        total=player->query_per();
                        break;*/
                default:
                        total=-1;//用-1标志类型出错！
        }
        return total;
}

int topten_del(string pid,string type)
{
        string str,*astr,*bstr,b_name,f_name;
        int i,j,k;
        
        switch(type)
        {
                case "rich":
                        b_name=RICH_B;
                        f_name=TOPTEN_RICH;
                        break;
                /*case "pker":
                        b_name=PKER_B;
                        f_name=TOPTEN_PKER;
                        break;*/
                case "exp":
                        b_name=EXP_B;
                        f_name=TOPTEN_EXP;
                        break;
                /*case "shen":
                        b_name=SHEN_B;
                        f_name=TOPTEN_SHEN;
                        break;*/
                case "neili":
                        b_name=NEILI_B;
                        f_name=TOPTEN_NEILI;
                        break;
                case "jingli":
                        b_name=JINGLI_B;
                        f_name=TOPTEN_JINGLI;
                        break;
                case "dushu":
                        b_name=DUSHU_B;
                        f_name=TOPTEN_DUSHU;
                        break;
                default:
                        return notify_fail("没有"+type+"这种排行榜！\n");
        }
        
        if(file_size(f_name)==-1)
                return notify_fail(b_name+"还没有创建！\n");
        
        str=read_file(f_name);
        
        astr=explode(str,"\n");
        for(i=0;i<sizeof(astr);i++)
        {
                //该行包括id则为真
                if(strsrch(astr[i],pid)!=-1)
                {
                        //为真表示该行只有一个id，即pid
                        if(strsrch(astr[i],";")==-1)
                        {
                                str="";
                                for(j=0;j<sizeof(astr);j++)
                                {
                                        if(j!=i)
                                                str+=astr[j]+"\n";
                                }
                                return topten_save(f_name,b_name,str);
                        }
                        else
                        {
                                bstr=explode(astr[i],";");
                                for(j=0;j<sizeof(bstr);j++)
                                {
                                        //说明该项即pid,应该去除
                                        if(strsrch(bstr[j],pid)!=-1)
                                        {
                                                astr[i]="";
                                                for(k=0;k<sizeof(bstr);k++)
                                                {
                                                        if(k!=j)
                                                        {
                                                                if((k+1)!=sizeof(bstr) && !((j+1)==sizeof(bstr) && j==(k+1)))
                                                                        astr[i]+=bstr[k]+";";
                                                                else
                                                                        astr[i]+=bstr[k];
                                                        }
                                                }
                                                //本来去除后j的循环应该停止,但是不影响结果
                                        }
                                        str=implode(astr,"\n");
                                }
                                return topten_save(f_name,b_name,str);
                        }
                }
        }
        return 1;
}

int topten_add(object player,string type)
{
        string str,name,id,b_name,f_name;
        string *astr;
        int i,j,data;
        
        //禁止巫师参加排行榜
        if(wizardp(player))
        return 0;
        if( query("id", player) == "idle")return 0;
        if( query("id", player) == "sao")return 0;
        
        switch(type)
        {
                case "rich":
                        b_name=RICH_B;
                        f_name=TOPTEN_RICH;
                        break;
                /*case "pker":
                        b_name=PKER_B;
                        f_name=TOPTEN_PKER;
                        break;*/
                case "exp":
                        b_name=EXP_B;
                        f_name=TOPTEN_EXP;
                        break;
                /*case "shen":
                        b_name=SHEN_B;
                        f_name=TOPTEN_SHEN;
                        break;*/
                case "neili":
                        b_name=NEILI_B;
                        f_name=TOPTEN_NEILI;
                        break;
                case "jingli":
                        b_name=JINGLI_B;
                        f_name=TOPTEN_JINGLI;
                        break;
                case "dushu":
                        b_name=DUSHU_B;
                        f_name=TOPTEN_DUSHU;
                        break;
                default:
                        return notify_fail("没有"+type+"这种排行榜！\n");
        }
        
        if(!objectp(player) || !userp(player))
                return 0;
        
        if(file_size(f_name)==-1)
        {
                str=query("name", player)+"("+query("id", player)+")"+get_all_data(player,type);
                return topten_save(f_name,b_name,str);
        }

        //主要程序！
        if(get_all_data(player,type)==-1)
                return notify_fail("数据查询错误，可能是查询类型错误！\n");
        
        //应该先排除该player的id!
        topten_del(query("id", player),type);
        str=read_file(f_name);
        astr=explode(str,"\n");
        i=0;
        
        while(i<sizeof(astr))
        {
                if(sscanf(astr[i],"%s(%s)%d",name,id,data)!=3) //|| sscanf(astr,"%s(%s)%d;%*s",name,id,data)!=3)
                        return notify_fail(b_name+"文件数据错误！请呼叫巫师！\n");
                
                str="";
                
                if(data<(int)get_all_data(player,type))
                {
                        //单独加入，暂时没考虑人数超过十行！
                        for(j=0;j<sizeof(astr);j++)
                        {
                                if( strsrch(astr[j],query("id", player)) != -1 && strsrch(astr[j],query("name", player)) != -1 )
                                        continue;

                                if(j==i)
                                        str+=query("name", player)+"("+query("id", player)+")"+get_all_data(player,type)+"\n";
                                str+=astr[j]+"\n";
                        }
                        return topten_save(f_name,b_name,str);
                }
                else
                if(data==(int)get_all_data(player,type))
                {
                        //并排加入
                        for(j=0;j<sizeof(astr);j++)
                        {
                                //by wenwu
                                if( strsrch(astr[j],query("id", player)) != -1 && strsrch(astr[j],query("name", player)) != -1 )
                                        continue;
                                
                                if(j==i)
                                        str+=astr[j]+";"+query("name", player)+"("+query("id", player)+")"+get_all_data(player,type)+"\n";
                                else
                                        str+=astr[j]+"\n";
                        }
                        return topten_save(f_name,b_name,str);
                }
                i++;
        }
        
        if(sizeof(astr)<MAX_LEAVE_TOP)
        {
                str=implode(astr,"\n")+"\n"+query("name", player)+"("+query("id", player)+")"+get_all_data(player,type);
                return topten_save(f_name,b_name,str);
        }
        return 0;
}
