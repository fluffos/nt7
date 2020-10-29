//                标准描述长度示例                                   |
// “小航海时代”游戏主支持
// by naihe  2003-06-19  于茂名



#include <ansi.h>
inherit ITEM;


#define B1                "灿烂夺目的黄金剑"        // 金剑  - YEL, HIY
#define B2                "装满金币的宝箱"        // 宝箱  - MAG, HIM
#define B3                "镶嵌钻石的金皇冠"        // 皇冠  - YEL, HIY
#define B4                "皇后的钻石项链"        // 项链  - CYN, HIC
#define B5                "圣洁的银杯"                // 银杯  - WHT, HIW
#define B6                "神秘的白金权杖"        // 权杖  - WHT, HIW
#define B7                "驱逐邪灵的圣十字架"        // 圣架  - HIM, HIM
#define B8                "预示未来的琉璃水晶"        // 水晶  - CYN, HIC
#define B9                "镶嵌红宝石的力量之戒"        // 宝戒  - RED, HIR
#define B10                "与希望同行的绿翡翠"        // 翡翠  - GRN, HIG


string game_now = "等待移动命令";
string att_now = "not_ok";
int target_hp, target_damage;
string pic_me, pic_target;



void new_game_set( int amount, string mark );
void map();
void check_hp();
object get_me();
string get_msg( int x, int y, string type );
void xunbaotu();
void fight_start( string who );
void be_attack();
void target_check_hp();


int finded_baowu( int which, string name )
{
        object me = get_me();
        int score;

        if( !me ) return 0;

        addn("be_finded", 1);
        set("b"+ which, HIW + query("b"+ which) );
        map();
        write(HIC"〖小航海时代〗  太幸运了！终于找到了 "+ name + " ！\n"NOR);

        if( query("be_finded") == 10 )
        {
                delete_temp("hanghai_gameing", me);
                game_now = "游戏结束";
                score = query("score");

                score += query("att_hp") * 500;
                score += query("att_jf") * 500;
                score += query("att_rs") * 500;
                score += query("att_yq") * 500;
                score += query("att_fd") * 500;

                score += query("hp") * 1000;

                if( score < 1 ) score = 1;
                addn("combat_exp", 500, me);

                write(HIY"
=========================================
             〖小航海时代〗

    你找齐了十件宝物！！游戏胜利结束了。
    你的最终得分是 "+score+" 分(仅供参考)。

    你获得了 500 点 经验值的奖励！
=========================================
\n"NOR);

                message_vision("$N成功地完成了 小航海时代 游戏！\n", me);
                remove_call_out("del_me");
                call_out("del_me", 1);
        }

        return 1;
}


// 获得“me”
object get_me()
{
        object me;
        if( !query("owner_id") ) return 0;

        me = find_player( query("owner_id") );
        if( !me ) return 0;
        return me;
}

// 获得攻击力段
int damage( int type )  // 6-11
{
        if( !type || type<1 || type>5 ) type = 1;

        switch( type )
        {
                case 1:        return ( 6+random(6) );
                case 2:        return ( 12+random(6) );
                case 3:        return ( 18+random(6) );
                case 4:        return ( 24+random(6) );
                case 5:        return ( 30+random(6) );
        }

        return (6+random(6));
}

void del_me()
{
        destruct( this_object() );
}

void create()
{
        set_name(HIY"经纬仪（游戏道具）"NOR, ({"jingwei yi","yi"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", "〖小航海时代〗游戏的主要道具，有了它才可以进行游戏。

查询现在的游戏状态，输入： game check
任何时候结束游戏，输入：   game over
\n");
                set("unit", "具");
                set("value", 0);
        }

        set("no_get", 1);
        set("no_drop",1);
        set("no_steal",1);
        set("no_give",1);
        setup();
}


void init()
{
        add_action("do_game", "game");
        add_action("do_go", "go");
        add_action("do_liaowang", "liaowang");
        add_action("do_attack", "atk");
}


void new_game(object me)
{
        if( !me ) return del_me();

        set("owner_id", getuid(me));
        set("owner_name",query("name", me));

// ******************************************
        new_game_set( 8, "岛屿" );

// ******************************************
        new_game_set( 4, "望远镜" );

// ******************************************
        new_game_set( 4, "报警探索仪" );

// ******************************************
        new_game_set( 4, "寻宝图" );

// ******************************************
//        new_game_set( 2, "旋涡" );
// 不要旋涡的设置！

// ******************************************
        new_game_set( 2, "冰山" );

// ******************************************
        new_game_set( 3, "补给品" );

// ******************************************
        new_game_set( 6, "海盗船" );

// ******************************************
        new_game_set( 6, "巨型章鱼" );

// ******************************************
        new_game_set( 6, "海藤精怪" );

// ******************************************
        new_game_set( 6, "火神鸟" );

// ******************************************
        new_game_set( 6, "幽灵船" );


// 宝物部分
// ******************************************
        new_game_set( 1, B1);
        new_game_set( 1, B2);
        new_game_set( 1, B3);
        new_game_set( 1, B4);
        new_game_set( 1, B5);
        new_game_set( 1, B6);
        new_game_set( 1, B7);
        new_game_set( 1, B8);
        new_game_set( 1, B9);
        new_game_set( 1, B10);

        new_game_set( 1, "当前船只位置");

        set("att_rb", 999999);
        set("att_hp", 1);
        set("att_jf", 1);
        set("att_rs", 1);
        set("att_yq", 1);
        set("att_fd", 1);
        set("hp", 100);

        write(">>>>>>>  各类武器及船只补给完毕。\n");
        set_temp("hanghai_gameing", "waiting_go", me);
        write("\n============ 设置成功！正在进入游戏…… ============\n");


        set("b1", YEL"金剑"NOR);
        set("b2", YEL"宝箱"NOR);
        set("b3", YEL"皇冠"NOR);
        set("b4", CYN"项链"NOR);
        set("b5", WHT"银杯"NOR);
        set("b6", WHT"权杖"NOR);
        set("b7", RED"圣架"NOR);
        set("b8", CYN"水晶"NOR);
        set("b9", RED"宝戒"NOR);
        set("b10",GRN"翡翠"NOR);

        call_out("game_start", 1);
}

void new_game_set( int amount, string mark )
{
        int x, y;
// 这里的 x, y ， x是竖数第几横，y是横数第几个。

        while( amount-- )
        {
                x = 1 + random(10);
                y = 1 + random(16);

                if( query( "aaa(" +x+ "," +y+ ")" ) )
                {
                        amount ++;
                        continue;
                }

                set( "aaa(" +x+ "," +y+ ")" , mark );
                if( mark == "当前船只位置" )
                {
                        set("now_x", x);
                        set("now_y", y);
                }
                if( mark == "岛屿" )
                        set("island("+x+","+y+")", "new" );

        }
        write( ">>>>>>>  " + mark + " 设置完毕。\n");
}

void game_start()
{
        object me = get_me();
        if( !me ) return del_me();

        set_temp("hanghai_gameing", "ok", me);
        message_vision("$N进入了 小航海时代 游戏！\n", me);

        write("\n**************************************
进入游戏成功！游戏目标为寻得10件宝物！
移动指令与 MUD 内相同。祝游戏愉快！
**************************************\n\n");

        map();
}


////////////////////////////////////
/////////  玩家操作函数  ///////////
////////////////////////////////////

int do_game(string arg)
{
        object me = this_player(), who;
        who = get_me();

        if( !who || me != who ) return 0;

        if( !arg || ( arg!= "check" && arg != "ck" && arg != "over") )
                return 0;

        if( !query_temp("hanghai_gameing", me) )
                return 0;

        if( arg == "check" || arg == "ck" )
        {
                map();
                return 1;
        }

        if( arg == "over" )
        {
           if( query_temp("hanghai_gameing", me) == "waiting_go" )
                   return 0;

                delete_temp("hanghai_gameing", me);
                message_vision("$N中途放弃，退出了 小航海时代 游戏。\n", me);
                write(HIR"\n  #########  已退出游戏，祝一切愉快！ #########\n\n"NOR);
                remove_call_out("del_me");
                call_out("del_me", 1);
                return 1;
        }
        return 1;
}

int do_go(string arg)
{
        object me = this_player(), who;
        int x, y, old_x, old_y, i;

        string * dirs = ({
"north", "south", "west", "east", "northwest", "northeast", "southwest", "southeast", });

        string here, msg;

        who = get_me();
        if( !who || who != me ) return 0;
        if( member_array( arg , dirs ) == -1 ) return 0;

        if( query_temp("hanghai_gameing", me) != "ok" )
                return notify_fail("现在不许移动！正在： "+ game_now + " 。\n");

        x = query("now_x");
        y = query("now_y");

        old_x = x;
        old_y = y;

        switch( arg )
        {
                case "north": x--; break;
                case "south": x++; break;
                case "west" : y--; break;
                case "east" : y++; break;
                case "northwest" : x--; y--; break;
                case "northeast" : x--; y++; break;
                case "southwest" : x++; y--; break;
                case "southeast" : x++; y++; break;
        }

        if( x<1 || y<1 || x>10 || y>16 )
                return notify_fail("这个方向已经无法前进了！\n");

        set("be_finded(" +old_x+ "," +old_y+ ")", 1); 


        if( query( "island(" +old_x+ "," +old_y+ ")" ) == "new"
        || query( "island(" +old_x+ "," +old_y+ ")" ) == "old" )
        {
                set("island(" +old_x+ "," +old_y+ ")", "old");
                set("aaa("+old_x+","+old_y+")", "旧的岛屿");
        }

        if( !query( "island(" +old_x+ "," +old_y+ ")" ) )
                delete("aaa(" +old_x+ "," +old_y+ ")" );

        here = query( "aaa(" +x+ "," +y+ ")" );

        set("aaa(" +x+ "," +y+ ")", "当前船只位置");
        set("now_x", x);
        set("now_y", y);

// 各类判断！！！

        if( here == "岛屿" )
        {
                addn("att_hp", 1);
                addn("att_jf", 1);
                addn("att_rs", 1);
                addn("att_yq", 1);
                addn("att_fd", 1);
                addn("hp", 20+random(11));
                if( query("hp") > 100 ) set("hp", 100);
                map();
                write(HIG"〖小航海时代〗  发现岛屿！得到了弹药补给和船只修理。\n"NOR);
                return 1;
        }

        if( here == "补给品" )
        {
                addn("hp", 20+random(11));
                if( query("hp") > 100 ) set("hp", 100);
                map();
                write(HIC"〖小航海时代〗  发现修补材料！船只得到了修理。\n"NOR);
                return 1;
        }

        if( here == "冰山" )
        {
                addn("hp", - (30+random(11)));
                map();
                write(HIR"〖小航海时代〗  糟糕！撞上了冰山！船受到了严重的损坏。\n"NOR);
                check_hp();
                return 1;
        }

        if( here == B1 )
                return finded_baowu( 1, B1 );
        if( here == B2 )
                return finded_baowu( 2, B2 );
        if( here == B3 )
                return finded_baowu( 3, B3 );
        if( here == B4 )
                return finded_baowu( 4, B4 );
        if( here == B5 )
                return finded_baowu( 5, B5 );
        if( here == B6 )
                return finded_baowu( 6, B6 );
        if( here == B7 )
                return finded_baowu( 7, B7 );
        if( here == B8 )
                return finded_baowu( 8, B8 );
        if( here == B9 )
                return finded_baowu( 9, B9 );
        if( here == B10 )
                return finded_baowu( 10, B10 );


        if( here == "望远镜" )
        {
                game_now = "了望中 （指令： liaowang x y）";
                map();
                write(HIM"〖小航海时代〗  发现了望远镜！输入 (liaowang x y) 指令查看该点周边海域的情形！ \n"NOR);
                set_temp("hanghai_gameing", "wangyuanjing", me);
                return 1;
        }

        if( here == "报警探索仪" )
        {
                map();
                write(HIM"〖小航海时代〗  发现了报警探索仪！\n"NOR);


                msg = HIM"\n报警仪探索中……自动探索 "+x+","+y+" 区域的情况。\n\n";

                msg += get_msg( x-1,y-1, "bjy" );
                msg += get_msg( x-1,y,   "bjy" );
                msg += get_msg( x-1,y+1, "bjy" );
                msg += get_msg( x,  y-1, "bjy" );
                msg +=         get_msg( x,  y,   "bjy" );
                msg +=         get_msg( x,  y+1, "bjy" );
                msg +=         get_msg( x+1,y-1, "bjy" );
                msg +=         get_msg( x+1,y,   "bjy" );
                msg +=         get_msg( x+1,y+1, "bjy" );

                msg += "\n探索危险区域报警完毕。\n\n"NOR;
                write( msg );
                return 1;
        }

        if( here == "寻宝图" )
        {
                map();
                write(HIC"〖小航海时代〗  发现了寻宝图！\n"NOR);
                xunbaotu();
                return 1;
        }


        if( here == "海盗船" || here == "火神鸟" || here == "海藤精怪"
         || here == "巨型章鱼" || here == "幽灵船" )
        {
                game_now = "与 "+ here+ " 战斗中！ 等待敌人攻击";
                set_temp("hanghai_gameing", "fighting", me);
                att_now = "not_ok";
                map();
                write(HIR"〖小航海时代〗  糟糕！遭遇了 "+ here+ " ！进入紧急战斗状态！！！\n"NOR);
                set("who_name", here);
                remove_call_out("fight_start");
                call_out("fight_start", 1, here);
                return 1;
        }


        map();
        write(HIW"〖小航海时代〗  漫漫航程，什么也没有发现……\n"NOR);
        return 1;
}

void map()
{
        string the_map = HIC"〖小航海时代〗  -- "HIR"HP："+query("hp")+"  宝物："+ query("be_finded")+NOR"\n\n        ", temp_map, temp2;
        int x, y, temp = 0;

        for( x=1; x<11; x++ )
        {
                for( y=1; y<17; y++ )
                {
                        if( temp == 16 )
                        {
                                temp = 0;
                                the_map += "\n        ";
                        }

                        temp2 = "("+x+","+y+")";

                        if( query( "be_finded"+temp2) )
                                temp_map = HIC"□"NOR;
                        else if( query("weixian"+temp2) )
                                temp_map = HIR"■"NOR;
                        else temp_map = HIC"■"NOR;
                        if( query( "aaa"+temp2 ) == "岛屿" )
                                temp_map = HIG"▲"NOR;
                        if( query( "aaa"+temp2 ) == "旧的岛屿" )
                                temp_map = HIG"△"NOR;
                        if( query( "aaa"+temp2 ) == "当前船只位置" )
                                temp_map = BLINK+HIY"≌"NOR;

                        the_map += temp_map;
                        temp++;
                }
        }

        the_map += "\n\n";

//        for( temp = 1;temp<11;temp++)
//        {
//                set("b"+temp, HIW+query("b"+temp) );
//        }

        the_map += sprintf( "          %s  %s  %s  %s  %s
          %s  %s  %s  %s  %s\n\n",
                query("b1"), query("b2"), query("b3"), 
                query("b4"), query("b5"), query("b6"), 
                query("b7"), query("b8"), query("b9"), 
                query("b10") );

        the_map += sprintf(HIW"  肉搏之刃(rb)：∞  火炮(hp)：%d  巨斧(jf)：  %d
  漫天飞刀(fd)：%d   鱼枪(yq)：%d  燃烧弹(rs)：%d\n"NOR,
                query("att_hp"), query("att_jf"), 
                query("att_fd"), query("att_yq"), query("att_rs") );




        write( HIY"================================================\n"NOR +the_map +
HIY"================================================\n"NOR"当前位置：("+ query("now_x") + "," + query("now_y") + ")  现在： "+ game_now +" \n");

}

void check_hp()
{
        object me = get_me();
        int x, y, temp = 0;
        string the_map, temp_map, temp2;

        if( !me ) call_out("del_me", 1);

        if( query("hp") > 0 ) return;

        the_map = HIR"\n〖小航海时代〗  -- 失败结果公布(共寻得"+query("be_finded")+"件宝物)\n\n        "NOR;

        for( x=1; x<11; x++ )
        {
                for( y=1; y<17; y++ )
                {
                        if( temp == 16 )
                        {
                                temp = 0;
                                the_map += "\n        ";
                        }

                        temp2 = query("aaa("+x+","+y+")");
                        temp_map = HIC"□"NOR;

                        if( temp2 == "海盗船" )
                                temp_map = HIR"盗"NOR;
                        if( temp2 == "巨型章鱼" )
                                temp_map = HIR"鱼"NOR;
                        if( temp2 == "海藤精怪" )
                                temp_map = HIR"藤"NOR;
                        if( temp2 == "火神鸟" )
                                temp_map = HIR"鸟"NOR;
                        if( temp2 == "幽灵船" )
                                temp_map = HIR"幽"NOR;
                        if( temp2 == "冰山" )
                                temp_map = HIW"冰"NOR;


                        if( temp2 == "岛屿" )
                                temp_map = HIG"▲"NOR;
                        if( temp2 == "旧的岛屿" )
                                temp_map = HIG"△"NOR;
                        if( temp2 == "当前船只位置" )
                                temp_map = BLINK+HIB"≌"NOR;

                        if( temp2 == B1 || temp2 == B2 || temp2 == B3
                         || temp2 == B4 || temp2 == B5 || temp2 == B6
                         || temp2 == B7 || temp2 == B8 || temp2 == B9 || temp2 == B10 )
                                temp_map = HIY"宝"NOR;

                        if( temp2 == "望远镜" )
                                temp_map = HIM"望"NOR;
                        if( temp2 == "报警探索仪" )
                                temp_map = HIM"警"NOR;
                        if( temp2 == "补给品" )
                                temp_map = HIM"补"NOR;
                        if( temp2 == "寻宝图" )
                                temp_map = HIM"图"NOR;

                        the_map += temp_map;
                        temp++;
                }
        }

        the_map += "\n\n";

        write( the_map );
        delete_temp("hanghai_gameing", me);
        game_now = "已经灭亡！";


        message_vision("$N游戏失败，退出了 小航海时代 游戏。\n", me);
        remove_call_out("game_over_over");
        call_out("game_over_over", 1);
        return;
}

void game_over_over()
{
        write(HIR"
=========================================
             〖小航海时代〗

      你的船只损坏得再也无法支持，
          终于沉入了大海之中！
=========================================
\n"NOR);
        remove_call_out("del_me");
        call_out("del_me", 1);
        return;
}

int do_liaowang( string arg )
{
        object me = this_player(), who;
        int x, y;
        string msg;

        who = get_me();
        if( !who || who != me ) return 0;

        if( query_temp("hanghai_gameing", me) != "wangyuanjing" )
                return 0;

        if( !arg || sscanf( arg, "%d %d", x, y ) != 2 )
                return notify_fail("请输入正确坐标！x -> 竖着数第几横  y -> 横着数第几个\n");
        if( x<1 || x>10 || y<1 || y>16 )
                return notify_fail("请输入正确坐标！x -> 竖着数第几横  y -> 横着数第几个\n");


        msg = HIM"了望中……你决定查看 "+x+","+y+" 区域的情况。\n\n";

        msg += get_msg( x-1,y-1, "wyj" );
        msg += get_msg( x-1,y,   "wyj" );
        msg += get_msg( x-1,y+1, "wyj" );
        msg += get_msg( x,  y-1, "wyj" );
        msg +=         get_msg( x,  y,   "wyj" );
        msg +=         get_msg( x,  y+1, "wyj" );
        msg +=         get_msg( x+1,y-1, "wyj" );
        msg +=         get_msg( x+1,y,   "wyj" );
        msg +=         get_msg( x+1,y+1, "wyj" );

        msg += "\n查看完毕。\n\n"NOR;

        write( msg );
        set_temp("hanghai_gameing", "ok", me);
        game_now = "等待移动命令";
        return 1;
}

string get_msg( int x, int y, string type )
{
        string msg;

        if( x<1 || x>10 || y<1 || y>16 ) return "";

        msg = query("aaa(" +x+ "," +y+ ")" );

        if( !msg )
        {
                if( type == "wyj" ) return "("+x+","+y+") -----------\n";
                return "";
        }

        if( msg == "冰山" || msg == "海盗船" || msg == "巨型章鱼"
         || msg == "海藤精怪" || msg == "火神鸟" || msg == "幽灵船" )
        {
                set("weixian("+x+","+y+")", 1);
                if( type == "wyj" ) return "("+x+","+y+") " + msg + "\n";
                return "("+x+","+y+") 有危险潜伏！\n";
        }

        if( type == "wyj" ) return "("+x+","+y+") " + msg + "\n";
        else return "";
}

void xunbaotu()
{
        int x, y;
        string msg;

        for( x = 1; x<11; x++ )
        {
                for( y=1;y<17;y++)
                {
                        msg = query("aaa(" +x+ "," +y+ ")" );
                        if( msg == B1 || msg == B2 || msg == B3 || msg == B4
                         || msg == B5 || msg == B6 || msg == B7 || msg == B8
                         || msg == B9 || msg == B10 )
                        {
                                write( HIM"("+x+","+y+")    该处藏有宝藏！\n"NOR);
                                return;
                        }
                }
        }
}

void fight_start( string who )
{
        switch( who )
        {
                case "海盗船": pic_target = "≌";target_damage=2; break;
                case "巨型章鱼": pic_target = "∝"; target_damage=4; break;
                case "海藤精怪": pic_target = "※"; target_damage=6; break;
                case "火神鸟": pic_target = "∮"; target_damage=8; break;
                case "幽灵船": pic_target = "≌"; target_damage=10; break;
        }

        target_hp = 50+ random(31);
        pic_me = "≌";

        remove_call_out("be_attack");
        call_out("be_attack", 1);
}

void be_attack()
{
        int damage;
        string pic1, pic2;

        damage = target_damage + random(3);
        addn("hp", -damage);

        pic1 = HIR + pic_target + " " + query("who_name") + "("+ target_hp + ")"NOR;
        pic2 = sprintf("    "HIG"(%|4d)航海者 "HIR"¤"NOR, query("hp"), pic_me);

        write( sprintf("
                     _ _ _ _ _ _ _ _ _ _       ATTACK!
            "HIR"-%-2d"NOR"    /                     `"HIY"¤"NOR"
%s                        %s
≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈\n\n", damage, pic2,  pic1));

        write(HIY"〖小航海时代〗  受到了 "+query("who_name")+ " 的攻击，船只损坏 "+ damage +" ！\n"NOR);
        check_hp();
        call_out("can_att", 1);
}

void can_att()
{
        if( query("hp") < 1 ) return;

        write(HIY"〖小航海时代〗  轮到你攻击了！(atk 方式)\n"NOR);
        write( sprintf(HIG"武器剩余：    rb:无限    hp:%d    jf:%d    rs:%d    yq:%d    fd:%d\n"NOR,
                query("att_hp"), query("att_jf"), query("att_rs"), query("att_yq"), query("att_fd") ) );
        game_now = "与 "+ query("who_name")+ " 战斗中！ 等待攻击指令";
        att_now = "ok";
}

int do_attack(string arg)
{
        object me = this_player(), who;
        string target_name = query("who_name"), pic1, pic2, temp;
        int damage;

        who = get_me();
        if( !who || who!=me ) return 0;

        if( att_now != "ok" ) return notify_fail("现在并不是你攻击的时候！\n");
        if( !arg || ( arg != "rb" && arg != "hp" && arg != "jf" && arg != "rs"
         && arg != "yq" && arg != "fd" ) )
                return notify_fail("你选择的武器不对！\n");

        if( query("att_"+ arg ) < 1 ) return notify_fail("这种武器已经没有了！\n");
        addn( "att_"+ arg , -1 );

        switch( arg )
        {
                case "rb":  temp = "肉搏之刃"; damage = damage(1); break;
                case "hp":
                        temp = "火炮";
                        if( target_name == "海盗船" ) damage = damage(5);
                        if( target_name == "巨型章鱼" ) damage = damage(4);
                        if( target_name == "海藤精怪" ) damage = damage(3);
                        if( target_name == "火神鸟" ) damage = damage(2);
                        if( target_name == "幽灵船" ) damage = damage(1);
                        break;
                case "jf":
                        temp = "巨斧";
                        if( target_name == "海盗船" ) damage = damage(4);
                        if( target_name == "巨型章鱼" ) damage = damage(1);
                        if( target_name == "海藤精怪" ) damage = damage(5);
                        if( target_name == "火神鸟" ) damage = damage(3);
                        if( target_name == "幽灵船" ) damage = damage(2);
                        break;
                case "rs":
                        temp = "燃烧弹";
                        if( target_name == "海盗船" ) damage = damage(2);
                        if( target_name == "巨型章鱼" ) damage = damage(3);
                        if( target_name == "海藤精怪" ) damage = damage(4);
                        if( target_name == "火神鸟" ) damage = damage(1);
                        if( target_name == "幽灵船" ) damage = damage(5);
                        break;
                case "yq":
                        temp = "鱼枪";
                        if( target_name == "海盗船" ) damage = damage(1);
                        if( target_name == "巨型章鱼" ) damage = damage(5);
                        if( target_name == "海藤精怪" ) damage = damage(2);
                        if( target_name == "火神鸟" ) damage = damage(4);
                        if( target_name == "幽灵船" ) damage = damage(3);
                        break;
                case "fd":
                        temp = "漫天飞刀";
                        if( target_name == "海盗船" ) damage = damage(3);
                        if( target_name == "巨型章鱼" ) damage = damage(2);
                        if( target_name == "海藤精怪" ) damage = damage(1);
                        if( target_name == "火神鸟" ) damage = damage(5);
                        if( target_name == "幽灵船" ) damage = damage(4);
                        break;
        }

        target_hp -= damage;
        addn("score", damage);

        pic1 = HIR"¤" + " " + query("who_name") + "("+ target_hp + ")"NOR;
        pic2 = sprintf("    "HIG"(%|4d)航海者 %s"NOR, query("hp"), pic_me);


        write( sprintf("
       %|8s！    _ _ _ _ _ _ _ _ _ _
                   "HIY"¤"NOR"                     \\    "HIR"-%d"NOR"
%s                        %s
≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈\n\n", temp,damage, pic2,  pic1));

        write(HIY"〖小航海时代〗  使用 "+ temp+ " 对 "+query("who_name")+ " 进行攻击！损害对方  "+ damage +" 。\n"NOR);

        att_now = "not_ok";
        remove_call_out("target_check_hp");
        call_out("target_check_hp", 1);

        return 1;
}

void target_check_hp()
{
        object me = get_me();
        if( !me )
        {
                remove_call_out("del_me");
                call_out("del_me", 1);
                return;
        }

        if( target_hp < 1 )
        {
                game_now = "等待移动命令";
                addn("hp", 1+(random(5)) );
                if( query("hp") > 100 ) set("hp", 100);
                map();
                write(HIG"\n〖小航海时代〗  打败了 "+query("who_name")+ " ！获得了少量的补给。继续出发吧！\n\n"NOR);
                set_temp("hanghai_gameing", "ok", me);
                addn("score", 100);
                return;
        }

        be_attack();
}
