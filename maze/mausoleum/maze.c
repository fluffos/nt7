// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit VRM_SERVER;
string openlock(string lock); // 外部调用开锁函数
varargs void init_data(object s, string arg);   // 初始化物件数据
string get_result(string str1, string str2);

mapping unlock = ([
// 对应房间可开启锁的序列A-B-C-D(3412)
        "A" : "123",
        "B" : "23",
        "C" : "134",
        "D" : "12",
]);

void create()
{
        //迷宫房间所继承的物件的档案名称。
        set_inherit_room( ROOM );

        //唯一房间
        set_unique_room( ({
                "/maze/mausoleum/unique_room/jiguan_a",
                "/maze/mausoleum/unique_room/jiguan_b",
                "/maze/mausoleum/unique_room/jiguan_c",
                "/maze/mausoleum/unique_room/jiguan_d",
        }) );

        //中心房间
        set_center_room("/maze/mausoleum/unique_room/enter");

        //迷宫房间里的怪物。
        set_maze_npcs( ([
                "/maze/mausoleum/npc/jiangling": random(2),
                "/maze/mausoleum/npc/qianrenzhang": random(2),
                "/maze/mausoleum/npc/bairenzhang": 1,
                "/maze/mausoleum/npc/bingshi": 1,
                "/maze/mausoleum/npc/baozi": random(2),
                "/maze/mausoleum/npc/tiger": random(2),
                "/maze/mausoleum/npc/lions": random(2),
                "/maze/mausoleum/npc/ni": 1,
                "/maze/mausoleum/npc/mammoth": random(2),
        ]) );

        set_lonely_create(1);

        //set_maze_boxs(5);

        //set_maze_traps(8);

        set_npcs_rate(40); 

        //迷宫的单边长
        set_maze_long(10);

        //入口方向(出口在对面)
        set_entry_dir("south");

        //出口与区域的连接方向
        set_link_exit_dir("north");

        //出口与区域的连接档案名
        set_link_exit_room("/d/luoyang/wenmiao");

        //普通房间描述
        set_maze_room_short(HIY "秦陵外宫" NOR);

        set_maze_room_desc(@LONG
自己站在长长的白玉石阶之底，石阶直通向上方那六丈来高、十里
来宽的巨大平台。仰头望去，广阔的黑色顶穹缀满了千万颗宝石、明珠，
光彩夺目，璀璨似星河，浩瀚如夜空，将四周照得一片皎皎明亮。在那
瑰丽的顶穹下方，赫然竟是一座拔地而起、连天入穹的雄伟宫城。那巍
峨壮丽的城楼殿宇，钩心斗角的流檐飞瓦，绵延雄矗于白玉石台上，如
泰山压顶，竟比长安城楼还要气势磅礴、雄奇瑰丽！石阶两边的广场上，
密密麻麻竟全是列成方阵的兵俑。铜人、陶俑、石雕……交相陈杂，少
说也有几万之众，军姿雄壮，威风凛凛。广场上，一条条银带蜿蜒交错，
闪耀着炫目的光泽，就像是江河汇集，一齐朝东面一个白光闪闪的水池
流去。
LONG);

        //入口房间短描述
        set_entry_short(HIR "秦陵外宫入口" NOR);

        //入口房间描述
        set_entry_desc(@LONG
自己站在长长的白玉石阶之底，石阶直通向上方那六丈来高、十里
来宽的巨大平台。仰头望去，广阔的黑色顶穹缀满了千万颗宝石、明珠，
光彩夺目，璀璨似星河，浩瀚如夜空，将四周照得一片皎皎明亮。在那
瑰丽的顶穹下方，赫然竟是一座拔地而起、连天入穹的雄伟宫城。那巍
峨壮丽的城楼殿宇，钩心斗角的流檐飞瓦，绵延雄矗于白玉石台上，如
泰山压顶，竟比长安城楼还要气势磅礴、雄奇瑰丽！石阶两边的广场上，
密密麻麻竟全是列成方阵的兵俑。铜人、陶俑、石雕……交相陈杂，少
说也有几万之众，军姿雄壮，威风凛凛。广场上，一条条银带蜿蜒交错，
闪耀着炫目的光泽，就像是江河汇集，一齐朝东面一个白光闪闪的水池
流去。
LONG);

        //出口房间短描述
        set_exit_short(HIW "秦陵外宫出口" NOR);

        //出口房间描述
        set_exit_desc(@LONG
自己站在长长的白玉石阶之底，石阶直通向上方那六丈来高、十里
来宽的巨大平台。仰头望去，广阔的黑色顶穹缀满了千万颗宝石、明珠，
光彩夺目，璀璨似星河，浩瀚如夜空，将四周照得一片皎皎明亮。在那
瑰丽的顶穹下方，赫然竟是一座拔地而起、连天入穹的雄伟宫城。那巍
峨壮丽的城楼殿宇，钩心斗角的流檐飞瓦，绵延雄矗于白玉石台上，如
泰山压顶，竟比长安城楼还要气势磅礴、雄奇瑰丽！石阶两边的广场上，
密密麻麻竟全是列成方阵的兵俑。铜人、陶俑、石雕……交相陈杂，少
说也有几万之众，军姿雄壮，威风凛凛。广场上，一条条银带蜿蜒交错，
闪耀着炫目的光泽，就像是江河汇集，一齐朝东面一个白光闪闪的水池
流去。
LONG);
        init_data();
}

// 外部调用此函数传递参数lock为: "A"-"D"
string openlock(object me, string lock)
{
        string opened, str_want_open;
        mixed result;
        int i;
        object s;
        string file;

        if( !stringp(query("lock/opened")) || query("lock/opened") == "" ) {
              set("lock/opened", unlock[lock]);
              return unlock[lock];
        }

        str_want_open = unlock[lock];
        opened = query("lock/opened");

        if (! stringp(opened))
              return "erros: opened is not a string.\n";

        result = get_result(opened, str_want_open);
        if( sizeof(result) == 4 && result == "3412" ) {
                file = FUBEN_D->query_maze_dir(me);
                set("lock/unlocked", 1);
                set("lock/opened", result);
                switch( TIME_D->realtime_digital_clock()[0..3] )
                {
                case "上午" :
                case "中午" :
                        if( !s = find_object(file + "southgate"))
                                s = load_object(file + "southgate");

                        set("exits/north", file+"maze2/entry", s);
                        break;
                case "下午" :
                        if( !s = find_object(file + "westgate"))
                                s = load_object(file + "westgate");

                        set("exits/east", file+"maze3/entry", s);
                        break;
                case "晚上" :
                        if( !s = find_object(file + "northgate"))
                                s = load_object(file + "northgate");

                        set("exits/south", file+"maze4/entry", s);
                        break;
                case "凌晨" :
                        if( !s = find_object(file + "eastgate"))
                                s = load_object(file + "eastgate");

                        set("exits/west", file+"maze1/entry", s);
                        break;
                default :
                        break;
                }

                tell_room(s, HIG "只听得轰隆隆几声，石门已陷入地下，露出了山洞的入口。\n" NOR);
                call_out("init_data", 180 + random(10), s, "enter"); // 三分钟后重新初始化所有数据
                return "UNLOCKED";
        }
        set("lock/opened", result);

        remove_call_out("init_data");

        return query("lock/opened");

}

varargs void init_data(object s, string arg)
{
        string* rn = ({ "A", "B", "C", "D" });
        int ran_num;

        // 随机分配房间参数，每次建立副本后顺序都不一样
        // 初试化个房间数据，各个房间数据统一交该物件管理，便于统一
        // 增加了解迷的难度
        ran_num = random(4);
        set("number/lockroom1", rn[ran_num]);

        rn -= ({ rn[ran_num] });
        ran_num = random(3);
        set("number/lockroom2", rn[ran_num]);

        rn -= ({ rn[ran_num] });
        ran_num = random(2);
        set("number/lockroom3", rn[ran_num]);

        rn -= ({ rn[ran_num] });
        set("number/lockroom4", rn[0]);

        set("lock/unlocked", 0); // 所有锁是否解开
        set("lock/opened", "");  // 已经打开的锁序列

        if( objectp(s) && arg == "enter" ) {
                tell_room(s, HIG "只听得轰隆隆几声，石门升起将山洞封住了。\n" NOR);
                delete("exits/west", s);
                delete("exits/east", s);
                delete("exits/south", s);
                delete("exits/north", s);
        }

        return;

}

string get_result(string str1, string str2)
{
        int n1, n2;
        string temp;

        if( !strcmp(str1, str2) ) return "";

        temp = "";

        for( n1=0; n1<sizeof(str1); n1++ ) {
                for( n2=0; n2<sizeof(str2); n2++ ) {
                      if( str2[n2..n2] == str1[n1..n1] )
                              temp += str2[n2..n2];
                }
        }

        if( temp == "" ) return str1 + str2;

        for( n1=0; n1<sizeof(temp); n1++ )
        {
                str1 = replace_string(str1, temp[n1..n1], "");
                str2 = replace_string(str2, temp[n1..n1], "");
        }

        return str1 + str2;
}
