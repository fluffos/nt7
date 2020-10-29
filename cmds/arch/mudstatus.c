// This program is a part of NT MudLIB

#include <i2d.h>
#include <message.h>
#include <ansi.h>
inherit F_CLEAN_UP;


#define I2D "/adm/daemons/intermud2_d.c"

//object I2D=load_object(I2D);

nosave mixed *current_status=({ ({}),({"$GRN$GB$NOR$",GB_CODE}),({"$RED$AD$NOR$",ANTI_AD}),({"$BLU$Ig$NOR$",IGNORED}),({}),({}),({"$GRN$GB$NOR$",GB_CODE}),({"$RED$AD$NOR$",ANTI_AD}),({"$BLU$Ig$NOR$",IGNORED}) });

void select_mud(int funct,int si,string *mud,string x)
{
        int input;
        string mudname;


        if( stringp(x) && x[0]=='q' )
        {
                tell(this_player(), "离开。\n", CMDMSG);
                return;
        }

        if( !sscanf(x,"%d",input) || input<0 || input > si )
        {
                tell(this_player(), "不合法的输入，请重新输入：\n", CMDMSG);
                input_to((: select_mud,funct,si,mud :));
                return;
        }
        mudname=mud[input];
        switch(funct)
        {
                case 1:if(I2D->set_status(mudname,GB_CODE)) tell(this_player(), "完成。\n", CMDMSG);return;
                case 2:if(I2D->set_status(mudname,ANTI_AD)) tell(this_player(), "完成。\n", CMDMSG);return;
                case 3:if(I2D->set_status(mudname,IGNORED)) tell(this_player(), "完成。\n", CMDMSG);return;
                case 6:if(I2D->set_status(mudname,-GB_CODE)) tell(this_player(), "完成。\n", CMDMSG);return;
                case 7:if(I2D->set_status(mudname,-ANTI_AD)) tell(this_player(), "完成。\n", CMDMSG);return;
                case 8:if(I2D->set_status(mudname,-IGNORED)) tell(this_player(), "完成。\n", CMDMSG);return;
        }

}

string test_status(string name,int status)
{
        if( I2D->fetch_data(name)["STATUS"] & status )
                return HIG"ENABLE"NOR;
        else return HIR"DISABLE"NOR;
}

void get_mud_name(int funct,string name)
{
        int si,i;
        string *mud;


        if( stringp(name) && name[0]=='q' )
        {
                tell(this_player(), "离开。\n", CMDMSG);
                return;
        }

        if( !sizeof(mud=I2D->fetch_mudname(name)) )
        {
                tell(this_player(), "抱歉，找不到站台，请重新输入。\n", CMDMSG);
                input_to((: get_mud_name,funct :));
                return;
        }
        //if( si=sizeof(mud)==1)
        //for(int i=0;i<=si;i++)
        //        printf("[%2d]\t\t%s\n",i,mud[i]);
        si=sizeof(mud);
        if( si == 1 )
        {
                select_mud(funct,si,mud,"0");
                return;
        }
        foreach(string x in mud)
        {
                //tell(this_player(),sprintf("[%4d] %s\n",i,x));
                tell(this_player(),sprintf("[%4d] %s %s[%s]\n",i,x,ansi(current_status[funct][0]),test_status(x,current_status[funct][1])));
                i++;
        }
        tell(this_player(), "请选择 0~"+(si-1), CMDMSG);
        input_to((: select_mud,funct,si,mud :));
        return;
}

void get_mud_ip(int funct,string name)
{
        int si,i;
        string *mud;


        if( stringp(name) && name[0]=='q' )
        {
                tell(this_player(), "离开。\n", CMDMSG);
                return;
        }

        if( !sizeof(mud=I2D->fetch_mudip(name)) )
        {
                tell(this_player(), "抱歉，找不到站台，请重新输入。\n", CMDMSG);
                input_to((: get_mud_ip,funct :));
                return;
        }
// fetch mud by ip
        si=sizeof(mud);
        if( si == 1 )
        {
                select_mud(funct,si,mud,"0");
                return;
        }
        foreach(string x in mud)
        {
                tell(this_player(),sprintf("[%4d] %s %s[%s]\n",i,x,ansi(current_status[funct][0]),test_status(x,current_status[funct][1])));
                i++;
        }
        tell(this_player(), "请选择 0~"+(si-1), CMDMSG);
        input_to((: select_mud,funct,si,mud :));
        return;


}
void select_target_way(int funct,string x)
{
        int *num=({1,2}),input;


        if(stringp(x) && x[0]=='q' )
        {
                tell(this_player(), "离开。\n", CMDMSG);
                return;
        }

        if( !sscanf(x,"%d",input) || member_array(input,num)==-1 )
        {
                tell(this_player(), "请输入[ 1~2 ] 的数字：\n", CMDMSG);
                input_to((: select_target_way,funct :));
                return;
        }

        switch(input)
        {
                case  1:tell(this_player(), "请输入站台名称：\n", CMDMSG);
                        input_to((: get_mud_name,funct :));
                        return;
                case  2:
                        tell(this_player(), "请输入站台 'IP:PORT'：\n", CMDMSG);
                        input_to((: get_mud_ip,funct :));
                        return;
        }
        return;
}

void add_mud_list(string name)
{
        string address;
        int port;

        if( stringp(name) && name[0]=='q' )
        {
                tell(this_player(), "离开。\n", CMDMSG);
                return;
        }

        if( sizeof(I2D->fetch_mudip(name)) )
        {
                tell(this_player(), "抱歉，已经有这个站台，请重新输入。\n", CMDMSG);
                input_to((: add_mud_list :));
                return;
        }

        if( sscanf(name, "%s:%d", address, port) != 2 )
        {
                tell(this_player(), "抱歉，格式不对，请重新输入。\n", CMDMSG);
                input_to((: add_mud_list :));
                return;
        }
        I2D->add_incoming_mudlist(address, port);
        tell(this_player(), "增加新站台成功。\n", CMDMSG);
        return;
}

void select_main_menu(string x)
{
        int *num=({1,2,3,5,6,7,8,9}),input;

        if(stringp(x) && x[0]=='q' )
        {
                tell(this_player(), "离开。\n", CMDMSG);
                return;
        }

        if( !sscanf(x,"%d",input) || member_array(input,num)==-1 )
        {
                tell(this_player(), "请输入[ 1~3,5~9 ] 的数字：\n", CMDMSG);
                input_to((: select_main_menu :));
                return;
        }
        if( input==5)
        {
                tell(this_player(), "请输入站台 'IP:PORT'：\n", CMDMSG);
                input_to((: add_mud_list :));
                return;
        }
        if( input==9)
        {
                if( fetch_variable("debug",find_object(I2D))==1 )
                {
                        I2D->debug();
                        tell(this_player(), "除错功能关闭。\n", CMDMSG);
                        return;
                } else {
                        I2D->debug();
                        tell(this_player(), "除错功能开启。\n", CMDMSG);
                        return;
                }
        }
        tell(this_player(), "1.手动输入站台名称\n2.手动输入 IP 位址\n\n", CMDMSG);
        switch(input)
        {
                case  1:tell(this_player(), "请选择你想增加 #转码# 功能的站台输入方式：\n", CMDMSG);
                        input_to((: select_target_way,1 :));break;
                case  2:tell(this_player(), "请选择你想增加 #广告# 功能的站台输入方式：\n", CMDMSG);
                        input_to((: select_target_way,2 :));break;
                case  3:tell(this_player(), "请选择你想增加 #忽略# 功能的站台输入方式：\n", CMDMSG);
                        input_to((: select_target_way,3 :));break;
                case  6:tell(this_player(), "请选择你想解除 #转码# 功能的站台输入方式：\n", CMDMSG);
                        input_to((: select_target_way,6 :));break;
                case  7:tell(this_player(), "请选择你想解除 #广告# 功能的站台输入方式：\n", CMDMSG);
                        input_to((: select_target_way,7 :));break;
                case  8:tell(this_player(), "请选择你想解除 #忽略# 功能的站台输入方式：\n", CMDMSG);
                        input_to((: select_target_way,8 :));break;

        }
        return;
}

int main(object me, string arg)
{
        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        if( !arg )
        {
                tell(me, "欢迎使用 Intermud2 Daemon Tool ！！\n", CMDMSG);
                tell(me, "请输入想使用的项目：\n"+@ITEM
[1]. 增加 #转码# 功能到某站( BIG5 <-> GB 间互转 )
[2]. 增加 #广告# 功能到某站( 将该站所有频道讯息转至 AD Channel )
[3]. 增加 #忽略# 功能到某站( 忽略所有该站所做的动作 )
[4]--(保留)
[5]. 增加某站到 mudlist
[6]. 解除某站的 #转码# 功能
[7]. 解除某站的 #广告# 功能
[8]. 解除某站的 #忽略# 功能
[9]. 除错功能变更( DEBUG Mode On/Off )
[q]. 离开。
请输入[ 1~3,5~9 ] 的数字：
ITEM, CMDMSG);
                input_to((: select_main_menu :));
                return 1;
        }
}
