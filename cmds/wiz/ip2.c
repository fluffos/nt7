/******** Written by ken@NT.  All rights reserved. ********/
//ip.c
/**********************************************************/
/* 用法∶ 除了用(ip id)本指令来查知对方IP，或玩家所在地外 */
/*        还可以由外部调用convert_ip函数，比如logind.c    */
/*        调用方法，假设ob是一个玩家，那么调用的方法如下  */
/*        "/cmds/adm/ip.c"->convert_ip(query_ip_number    */
/*        (ob)) 这样就会返回一个字符串类型的ob的所在地。  */
/*                                                        */
/* 更新∶ 数据库放在/adm/etc/ipdata/ 分别放著五个己分类   */
/*        的IP数据文件，如发现有未知IP，可以自行更新。    */
/*                                                        */
/* 准确∶ 准确度完全取决于数据库，本程序是这样实现IP查找  */
/*        的，一个IP由四个IP段所组成，A.B.C.D 先找到IP的  */
/*        A段，这决定在/ipdata/里的那个文件中查找，大大加 */
/*        快了查找到速度，然后查找query_ip_number(ob)是否 */
/*        在和IP1和IP2之间是就反回后面的地区名，不是就找下*/
/*        一行，到最后也不到返回未知地区。( by ken@NT )   */
/**********************************************************/

#include <ansi.h>
inherit F_CLEAN_UP;

#define IP_DIR "/adm/etc/ipdata/" // IP数据所放的位置
#define EXT    ".ip" // 定义IP数据文件的副档名

int help(object me);
int main(object me, string arg);

string convert_ip(string ip); // 给外部调用的函数

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string ip,output;
        object ob;

        if (!SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;
                
        if (!arg || sscanf(arg, "%s", ip) != 1)
                return help(me);

        seteuid(geteuid(me));
        ob = UPDATE_D->global_find_player(arg);
        if (objectp(ob))
        {
                ip     = query_ip_number(ob); // 在玩家身上取得IP                               
                output = convert_ip(ip);
                UPDATE_D->global_destruct_player(ob, 1);
                write(output + "\n");
                return 1;
        }
        else
        {
                output = convert_ip(ip);
                write(output + "\n");
                return 1;
        }
}

string convert_ip(string ip)
{
        string  *ip_data_detail, *ip_data, *ip_detail;
        int a, b, c, d, i, count,  ipa, ipb, ipc, find = 0;
        
        if (!stringp(ip))
                return "";
        if (sscanf(ip, "%d.%d.%d.%d", a, b, c, d) != 4)
                return "";
        
        ip_detail = explode(ip, ".");
        // 把cut开做四段，如果IP= 127.0.0.1 那么ip_detail[0] = 127                                 
        // ip_detail[1] = 0 ip_detail[2] = 0 ip_detail[3] = 1
        // 考虑到效率的问题，先判断ip_detail[0]是什么，再打开对应的IP文件
        // 当然IP文件要先经过分类(即是ip_detail[0].ip放著的所有IP都是以此开头)
        if (file_size(IP_DIR + ip_detail[0] + EXT) > 0)
        {
                ip_data = explode(read_file(IP_DIR + ip_detail[0] + EXT), "\n");
        }
        
        else if (file_size(IP_DIR + "0" + EXT) > 0)
        { 
                ip_data = explode(read_file(IP_DIR + "0" + EXT), "\n");
        }

        sscanf(ip, "%d.%d.%d.%d", a, b, c, d);
        // 把IP每段强制性变为3个字符，比如 127.0.0.1 变成127.000.000.001
        ip_detail[0] = sprintf("%03d", a );
        ip_detail[1] = sprintf("%03d", b );
        ip_detail[2] = sprintf("%03d", c );
        ip_detail[3] = sprintf("%03d", d );
        
        ip     = implode(ip_detail, ".");
        sscanf(ip, "%d.%d.%d.%d", a, b, c, d); // 把IP的字串变成整数类型
        ipb = d + (c * 1000) + (b * 1000000); // 把尾三段的IP相加，用作下面的运算

        count  = sizeof (ip_data);
        count  = count - 1;

        if  (ip == "127.000.000.001")
        {
                return "本地机器";
                find = 1;
        }
        if (find != 1)
        {               
                for (i=0; i<=count; i++)
                {
                        ip_data_detail = explode(ip_data[i], "|");
                        if(strcmp (ip[0..2], ip_data_detail[0][0..2]) != 0 &&
                           strcmp (ip[0..2], ip_data_detail[1][0..2]) != 0)
                        continue; // 如果IP的第一段完全相等于IP文件里的IP头一段则执行下面代码
                        {                       
                                sscanf(ip_data_detail[0], "%d.%d.%d.%d", a, b, c, d);
                                ipa = d + (c * 1000) + (b * 1000000);
                                // ipa 是记著IP1尾三段的IP相加后的值
                                sscanf(ip_data_detail[1], "%d.%d.%d.%d", a, b, c, d);
                                ipc = d + (c * 1000) + (b * 1000000);
                                // ipc 记著IP2尾三段的IP相加后的值
                                // 如果玩家的IP是在ipa 和 ipc 之间的，即执行下面代码
                                if (ipb <= ipa || ipb >= ipc)
                                continue;                       
                                {                       
                                        return ip_data_detail[2]; // 传回该IP的地区
                                        find = 1;
                                        break;
                                }
                        }
                }
        }

        if (find == 0)
                return "未知地区";

}

int help(object me)
{
write(@HELP
Written by ken@NT. All rights reserved.
E-mail: printken@yahoo.com.hk

格式 : ip <IP地址 | 在线玩家>

HELP);
return 1;
}