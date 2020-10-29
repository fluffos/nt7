// /job/japan/haizhan_master.c
// by akuma 10:57 AM 11/30/2003
// source by naihe  2003-06-19  于茂名

#include <ansi.h>
inherit ITEM;

#define B1                "吉野的舰旗"                // 金剑  - YEL, HIY
#define B2                "敌舰的主炮"                // 宝箱  - MAG, HIM
#define B3                "轮机油箱"                // 皇冠  - YEL, HIY
#define B4                "敌军官的头盔"                // 项链  - CYN, HIC

string game_now = "等待指示命令……";
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
        int score;
        object me = get_me();

        if ( !me ) return 0;

        addn("be_finded", 1);
        set("b" + which, HIW + query("b" + which) );
        map();
        write(HIC"太幸运了，终于找到了" + name + "。\n"NOR);

        if ( query("be_finded") == 4 ) {
                message_vision("$N成功地找到全部四件战利品，获得两百量黄金的奖励。\n", me);
                addn("balance", 2000000, me);
        }
        return 1;
}

object get_me()                // 获得“me”
{
        object me;

        if ( !query("owner_id") ) return 0;

        me = find_player( query("owner_id") );
        if ( !me ) return 0;
        return me;
}

int damage( int type )  // 获得攻击力段 6-11
{
        if ( !type || type < 1 || type > 5 ) type = 1;

        switch( type ) {
                case 1: return ( 3 + random(1) );
                case 2: return ( 5 + random(2) );
                case 3: return ( 8 + random(3) );
                case 4: return ( 12 + random(4) );
                case 5: return ( 15 + random(5) );
        }
        return (6 + random(6));
}

void del_me()
{
        object me = get_me();

        if ( !me ) return;

        me->move("/d/tianjin/navy03");
        delete_temp("hanzai_cond", me);
        set("job_done", "fleet_job", me);
        addn("job/fleet", 1, me);
        destruct( this_object() );
}

void create()
{
        set_name(HIY"经纬仪"NOR, ({"jingwei yi","yi"}));
        set_weight(1);
        if ( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", @LONG
控制战船的主要工具，有了它才可以进行甲午海战战场。

查询战斗状态，输入： combat check
退出战斗状态，输入： combat over
LONG);
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
        add_action("do_game", "combat");
        add_action("do_go", "ship");
        add_action("do_liaowang", "liaowang");
        add_action("do_attack", "fire");
}


void new_game(object me)
{
        if ( !me ) return del_me();

        set("owner_id", getuid(me));
        set("owner_name",query("name", me));

        new_game_set( random(3) + 3, "岛屿" );
        new_game_set( 2, "望远镜" );
        new_game_set( 2, "报警探索仪" );
        new_game_set( 2, "寻宝图" );
        new_game_set( 1, "补给船" );
        new_game_set( 5, "登陆艇" );
        new_game_set( 12, "炮艇" );
        new_game_set( 8, "驱逐舰" );
        new_game_set( 8, "巡洋舰" );
        new_game_set( 5, "潜艇" );
        new_game_set( 2, "吉野号" );

        new_game_set( 1, B1);
        new_game_set( 1, B2);
        new_game_set( 1, B3);
        new_game_set( 1, B4);

        new_game_set( 1, "当前旗舰位置");

        set("att_肉搏", 999999);
        set("att_弓箭", 40);
        set("att_石炮", 10);
        set("att_火炮", 5);
        set("att_燃烧弹", 3);
        set("att_鱼雷", 2);
        set("hp", 150);

        set_temp("haizai_cond", "waiting_go", me);
        write("\n============ 设置成功！正在进入游戏…… ============\n");

        set("b1", YEL"吉野的舰旗"NOR);
        set("b2", YEL"敌舰的主炮"NOR);
        set("b3", YEL"轮机油箱"NOR);
        set("b4", CYN"敌军官的头盔"NOR);

        call_out("game_start", 1);
}

void new_game_set( int amount, string mark )
{
        int x, y;        // 这里的 x, y ， x是竖数第几横，y是横数第几个。

        while ( amount-- ) {
                x = 1 + random(100);
                y = 1 + random(160);

                if ( query( "aaa(" + x + "," + y + ")" ) ) {
                        amount ++;
                        continue;
                }
                set( "aaa(" + x + "," + y + ")" , mark );
                if ( mark == "当前旗舰位置" ) {
                        set("now_x", x);
                        set("now_y", y);
                }
                if ( mark == "岛屿" )
                        set("island(" + x + "," + y + ")", "new" );
        }
}

void game_start()
{
        object me = get_me();

        if ( !me ) return del_me();

        set_temp("haizhan_cond", "ok", me);
        message_vision("$N进入进入海战战场，左右北洋水师相互协应\n", me);

        write("\n战斗目标：消灭日本水师旗舰。\n");
        map();
}
////////////////////////////////////
/////////  玩家操作函数  ///////////
////////////////////////////////////
int do_game(string arg)
{
        int exp;
        object me = this_player(), who;

        who = get_me();

        if ( !who || me != who ) return 0;

        if ( !arg || ( arg!= "check" && arg != "ck" && arg != "over") ) return 0;

        if( !query_temp("haizhan_cond", me))return 0;

        if ( arg == "check" || arg == "ck" ) {
                map();
                return 1;
        }
        if ( arg == "over" ) {
                delete_temp("haizhan_cond", me);
                message_vision("$N中途退出海战。\n", me);
                exp = 1000 + random(1000);
                write(HIR"\n由於临阵脱逃，损失经验值" + exp + "点。\n"NOR);
                addn("combat_exp", -exp, me);
                remove_call_out("del_me");
                call_out("del_me", 1);
                return 1;
        }
        return 1;
}

int do_go(string arg)
{
        int x, y, old_x, old_y, i;
        string *dirs = ({ "north", "south", "west", "east", "northwest", "northeast", "southwest", "southeast", });
        string here, msg;
        object me = this_player(), who, obj;

        who = get_me();

        if ( !who || who != me ) return 0;
        if ( member_array( arg , dirs ) == -1 ) return 0;

        if( query_temp("haizhan_cond", me) != "ok")return notify_fail("现在不许移动。正在："+game_now+"。\n");

        x = query("now_x");
        y = query("now_y");

        old_x = x;
        old_y = y;

        switch ( arg ) {
                case "north": x--; break;
                case "south": x++; break;
                case "west" : y--; break;
                case "east" : y++; break;
                case "northwest" : x--; y--; break;
                case "northeast" : x--; y++; break;
                case "southwest" : x++; y--; break;
                case "southeast" : x++; y++; break;
        }
        if ( x < 1 || y < 1 || x > 12 || y > 18 ) return notify_fail("这个方向已经无法前进了！\n");

        set("be_finded(" + old_x + "," + old_y + ")", 1); 

        if ( query( "island(" + old_x + "," + old_y + ")" ) == "new" || query( "island(" + old_x + "," + old_y + ")" ) == "old" ) {
                set("island(" + old_x + "," + old_y + ")", "old");
                set("aaa("+old_x+","+old_y+")", "旧的岛屿");
        }
        if ( !query( "island(" + old_x + "," + old_y + ")" ) ) delete("aaa(" + old_x + "," + old_y + ")" );

        here = query( "aaa(" + x + "," + y + ")" );

        set("aaa(" +x+ "," +y+ ")", "当前旗舰位置");
        set("now_x", x);
        set("now_y", y);

        // 各类判断！！！
        if ( here == "岛屿" ) {
                addn("att_弓箭", 10);
                addn("att_石炮", 4);
                addn("att_火炮", 2);
                addn("att_燃烧弹", 1);
                addn("att_鱼雷", 1);
                addn("hp", 20 + random(11));
                map();
                write(HIG"发现岛屿！得到了弹药补给和船只修理。\n"NOR);
                if ( random(100) > 80 ) {
                        write(HIG"突然，一名日本武士从岛上隐蔽处冲上了你的坐船……\n"NOR);
                        obj = new(__DIR__"killer3");
                        set("target",query("id",  me), obj);
                        obj->move(environment(me));
                }
                return 1;
        }
        if ( here == "登陆艇" ) {
                write(HIG"突然，一名日本武士从登陆艇冲上了你的坐船……\n"NOR);
                obj = new(__DIR__"killer3");
                map();
                set("target",query("id",  me), obj);
                obj->move(environment(me));
                return 1;
        }
        if ( here == "补给船" ) {
                addn("hp", 30 + random(21));
                map();
                write(HIC"发现修补材料！船只得到了修理。\n"NOR);
                return 1;
        }
        if ( here == B1 ) return finded_baowu( 1, B1 );

        if ( here == B2 ) return finded_baowu( 2, B2 );

        if ( here == B3 ) return finded_baowu( 3, B3 );

        if ( here == B4 ) return finded_baowu( 4, B4 );

        if ( here == "望远镜" ) {
                game_now = "了望中 （指令： liaowang x y）";
                map();
                write(HIM"发现了望远镜！输入 (liaowang x y) 指令查看该点周边海域的情形！ \n"NOR);
                set_temp("haizhan_cond", "wangyuanjing", me);
                return 1;
        }
        if ( here == "报警探索仪" ) {
                map();
                write(HIM"发现了报警探索仪！\n"NOR);

                msg = HIM"\n报警仪探索中……自动探索 " + x + "," + y + " 区域的情况。\n\n";
                msg += get_msg( x - 1, y - 1, "bjy" );
                msg += get_msg( x - 1, y, "bjy" );
                msg += get_msg( x - 1, y + 1, "bjy" );
                msg += get_msg( x, y - 1, "bjy" );
                msg +=  get_msg( x, y,   "bjy" );
                msg +=  get_msg( x, y + 1, "bjy" );
                msg +=  get_msg( x + 1, y - 1, "bjy" );
                msg +=  get_msg( x + 1, y, "bjy" );
                msg +=  get_msg( x + 1, y + 1, "bjy" );
                msg += "\n探索危险区域报警完毕。\n\n"NOR;
                write( msg );
                return 1;
        }
        if ( here == "寻宝图" ) {
                map();
                write(HIC"发现了一张寻宝图。\n"NOR);
                xunbaotu();
                return 1;
        }
        if ( here == "炮艇" || here == "驱逐舰" || here == "巡洋舰" || here == "潜艇" || here == "吉野号" ) {
                game_now = "与 " + here + " 战斗中！ 等待敌人攻击";
                set_temp("haizhan_cond", "fighting", me);
                att_now = "not_ok";
                map();
                write(HIR"糟糕……遭遇了 " + here + "。进入紧急战斗状态！\n"NOR);
                set("who_name", here);
                remove_call_out("fight_start");
                call_out("fight_start", 1, here);
                return 1;
        }
        map();
        write(HIW"舰队在海中行使，尚未发现敌情……\n"NOR);
        return 1;
}

void map()
{
        int x, y, temp = 0;
        string the_map = HIC"  -- "HIR"HP：" + query("hp") + "  战利品：" + query("be_finded") + NOR"\n    ", temp_map, temp2;

        for ( x = 1; x < 103; x++ ) {
                for( y = 1; y < 40; y++ ) {
                        if ( temp == 39 ) {
                                temp = 0;
                                the_map += "\n    ";
                        }
                        temp2 = "(" + x + "," + y + ")";

                        if ( query( "be_finded" + temp2) ) temp_map = HIC"□"NOR;
                        else if ( query("weixian" + temp2) ) temp_map = HIR"■"NOR;
                        else temp_map = HIC"■"NOR;

                        if ( query( "aaa" + temp2 ) == "岛屿" ) temp_map = HIG"▲"NOR;
                        if ( query( "aaa" + temp2 ) == "旧的岛屿" ) temp_map = HIG"△"NOR;
                        if ( query( "aaa" + temp2 ) == "当前旗舰位置" ) temp_map = BLINK+HIY"≌"NOR;

                        the_map += temp_map;
                        temp++;
                }
        }
        the_map += "\n\n";

        the_map += sprintf( "      %s  %s  %s  %s  \n", query("b1"), query("b2"), query("b3"), query("b4") );

        the_map += sprintf(HIW"  肉搏：∞  弓箭：%d  石炮：%d  火炮：%d   燃烧弹：%d  鱼雷：%d\n"NOR,
                query("att_弓箭"), query("att_石炮"), query("att_火炮"), query("att_燃烧弹"), query("att_鱼雷") );

        write( HIY"================================================\n"NOR + the_map +
                HIY"================================================\n"NOR"当前位置：(" + query("now_x") + "," + query("now_y") + ")  现在： " +
                game_now + " \n");
}

void check_hp()
{
        int x, y, temp = 0;
        string the_map, temp_map, temp2;
        object me = get_me();

        if ( !me ) call_out("del_me", 1);

        if ( query("hp") > 0 ) return;

        the_map = HIR"\n  -- 失败结果公布(共寻得" + query("be_finded") + "件战利品)\n\n        "NOR;

        for( x = 1; x < 11; x++ ) {
                for ( y = 1; y < 17; y++ ) {
                        if ( temp == 16 ) {
                                temp = 0;
                                the_map += "\n        ";
                        }
                        temp2 = query("aaa("+x+","+y+")");
                        temp_map = HIC"□"NOR;

                        if ( temp2 == "跑船" ) temp_map = HIR"跑"NOR;
                        if ( temp2 == "巡洋舰" ) temp_map = HIR"巡"NOR;
                        if ( temp2 == "驱逐舰" ) temp_map = HIR"驱"NOR;
                        if ( temp2 == "潜艇" ) temp_map = HIR"潜"NOR;
                        if ( temp2 == "吉野号" ) temp_map = HIR"主"NOR;



                        if ( temp2 == "岛屿" ) temp_map = HIG"▲"NOR;
                        if ( temp2 == "旧的岛屿" ) temp_map = HIG"△"NOR;
                        if ( temp2 == "当前旗舰位置" ) temp_map = BLINK+HIB"≌"NOR;

                        if ( temp2 == B1 || temp2 == B2 || temp2 == B3 || temp2 == B4 )
                                temp_map = HIY"品"NOR;

                        if ( temp2 == "望远镜" ) temp_map = HIM"望"NOR;
                        if ( temp2 == "报警探索仪" ) temp_map = HIM"警"NOR;
                        if ( temp2 == "补给船" ) temp_map = HIM"补"NOR;
                        if ( temp2 == "寻宝图" ) temp_map = HIM"图"NOR;

                        the_map += temp_map;
                        temp++;
                }
        }
        the_map += "\n\n";

        write( the_map );
        delete_temp("haizhan_cond", me);
        game_now = "已经灭亡。";

        message_vision("$N的坐舰被击沉。\n", me);
        if ( random( (int)me->query_skill("swimming", 1) ) < 80 ) {
                set_temp("last_damage_from", "坐舰被击沉，淹", me);
                me->die();
        }
        else {
                tell_object(me, CYN"你奋力向岸边游去，虽然根本就看不见岸在哪里……\n"NOR);
                me->unconcious();
        }
        remove_call_out("game_over_over");
        call_out("game_over_over", 1);
        return;
}

void game_over_over()
{
        write(HIR"战争结束了……\n"NOR);
        remove_call_out("del_me");
        call_out("del_me", 1);
        return;
}

int do_liaowang( string arg )
{
        int x, y;
        string msg;
        object me = this_player(), who;

        who = get_me();

        if ( !who || who != me ) return 0;

        if( query_temp("haizhan_cond", me) != "wangyuanjing")return 0;

        if ( !arg || sscanf( arg, "%d %d", x, y ) != 2 ) return notify_fail("请输入正确坐标！x -> 竖着数第几横  y -> 横着数第几个\n");

        if ( x < 1 || x > 10 || y < 1 || y > 16 ) return notify_fail("请输入正确坐标！x -> 竖着数第几横  y -> 横着数第几个\n");


        msg = HIM"了望中……你决定查看 " + x + "," + y + " 区域的情况。\n\n";

        msg += get_msg( x-1,y-1, "wyj" );
        msg += get_msg( x-1,y,   "wyj" );
        msg += get_msg( x-1,y+1, "wyj" );
        msg += get_msg( x,  y-1, "wyj" );
        msg +=  get_msg( x,  y,   "wyj" );
        msg +=  get_msg( x,  y+1, "wyj" );
        msg +=  get_msg( x+1,y-1, "wyj" );
        msg +=  get_msg( x+1,y,   "wyj" );
        msg +=  get_msg( x+1,y+1, "wyj" );

        msg += "\n查看完毕。\n"NOR;

        write( msg );
        set_temp("haizhan_cond", "ok", me);
        game_now = "等待移动命令";
        return 1;
}

string get_msg( int x, int y, string type )
{
        string msg;

        if ( x<1 || x>10 || y<1 || y>16 ) return "";

        msg = query("aaa(" + x + "," + y + ")" );

        if ( !msg ) {
                if( type == "wyj" ) return "(" + x + "," + y + ") -----------\n";
                return "";
        }
        if ( msg == "炮艇" || msg == "驱逐舰" || msg == "巡洋舰" || msg == "潜艇" || msg == "吉野号" ) {
                set("weixian(" + x + "," + y + ")", 1);
                if( type == "wyj" ) return "(" + x + "," + y + ") " + msg + "\n";
                return "("+x+","+y+") 有危险潜伏！\n";
        }
        if ( type == "wyj" ) return "(" + x + "," + y + ") " + msg + "\n";
        else return "";
}

void xunbaotu()
{
        int x, y;
        string msg;

        for ( x = 1; x < 11; x++ ) {
                for ( y = 1; y < 17; y++ ) {
                        msg = query("aaa(" +x+ "," +y+ ")" );
                        if ( msg == B1 || msg == B2 || msg == B3 || msg == B4 ) {
                                write( HIM"(" + x + "," + y + ")    该处藏有战利品\n"NOR);
                                return;
                        }
                }
        }
}

void fight_start( string who )
{
        switch ( who ) {
                case "炮艇": pic_target = "≌"; target_damage = 1; break;
                case "驱逐舰": pic_target = "≌"; target_damage = 2; break;
                case "巡洋舰": pic_target = "∝"; target_damage = 4; break;
                case "潜艇": pic_target = "※"; target_damage = 6; break;
                case "吉野号": pic_target = "∮"; target_damage = 10; break;
        }
        if ( who == "吉野号" ) target_hp = 110 + random(31);
        else target_hp = 70 + random(31);
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

        write( sprintf("\n                     _ _ _ _ _ _ _ _ _ _       ATTACK！\n            "HIR"-%-2d"NOR"    /                     `"HIY"¤"NOR +
                "\n%s                        %s\n≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈\n\n", damage, pic2,  pic1));

        write(HIY"你的坐船受到了" + query("who_name") +  "的攻击，船只损坏" + damage + "。\n"NOR);
        check_hp();
        call_out("can_att", 1);
}

void can_att()
{
        if ( query("hp") < 1 ) return;

        write(HIY"轮到你攻击了。(fire 方式)\n"NOR);
        write( sprintf(HIG"武器剩余：    肉搏：无限    弓箭：%d    石炮：%d    火炮：%d    燃烧弹：%d    鱼雷：%d\n"NOR,
                query("att_弓箭"), query("att_石炮"), query("att_火炮"), query("att_燃烧弹"), query("att_鱼雷") ) );
        game_now = "与 " + query("who_name") + " 战斗中。等待攻击指令……";
        att_now = "ok";
}

int do_attack(string arg)
{
        int damage, miss;
        string target_name = query("who_name"), pic1, pic2, temp;
        object me = this_player(), who;

        who = get_me();
        if ( !who || who != me ) return 0;

        if ( att_now != "ok" ) return notify_fail("现在并不是你攻击的时候。\n");

        if ( !arg || ( arg != "肉搏" && arg != "弓箭" && arg != "石炮" && arg != "火炮" && arg != "燃烧弹" && arg != "鱼雷" ) )
                return notify_fail("你选择的武器不对。\n");

        if ( query("att_"+ arg ) < 1 ) return notify_fail("这种武器已经没有了。\n");
        addn( "att_"+ arg , -1 );

        temp = arg;
        switch ( arg ) {
                case "肉搏":
                        miss = 5;
                        damage = damage(1);
                        break;
                case "弓箭":
                        miss = 10;
                        if ( target_name == "炮艇" ) damage = damage(5);
                        if ( target_name == "驱逐舰" ) damage = damage(4);
                        if ( target_name == "巡洋舰" ) damage = damage(3);
                        if ( target_name == "潜艇" ) damage = damage(2);
                        if ( target_name == "吉野号" ) damage = damage(1);
                        break;
                case "石炮":
                        miss = 15;
                        if ( target_name == "炮艇" ) damage = damage(4);
                        if ( target_name == "驱逐舰" ) damage = damage(1);
                        if ( target_name == "巡洋舰" ) damage = damage(5);
                        if ( target_name == "潜艇" ) damage = damage(3);
                        if ( target_name == "吉野号" ) damage = damage(2);
                        break;
                case "火炮":
                        miss = 20;
                        if ( target_name == "炮艇" ) damage = damage(2);
                        if ( target_name == "驱逐舰" ) damage = damage(3);
                        if ( target_name == "巡洋舰" ) damage = damage(5);
                        if ( target_name == "潜艇" ) damage = damage(1);
                        if ( target_name == "吉野号" ) damage = damage(4);
                        break;
                case "燃烧弹":
                        miss = 30;
                        if ( target_name == "炮艇" ) damage = damage(1);
                        if ( target_name == "驱逐舰" ) damage = damage(5);
                        if ( target_name == "巡洋舰" ) damage = damage(2);
                        if ( target_name == "潜艇" ) damage = damage(4);
                        if ( target_name == "吉野号" ) damage = damage(3);
                        break;
                case "鱼雷":
                        miss = 20;
                        if ( target_name == "炮艇" ) damage = damage(3);
                        if ( target_name == "驱逐舰" ) damage = damage(2);
                        if ( target_name == "巡洋舰" ) damage = damage(1);
                        if ( target_name == "潜艇" ) damage = damage(4);
                        if ( target_name == "吉野号" ) damage = damage(5);
                        break;
        }
        pic1 = HIR"¤" + " " + query("who_name") + "("+ target_hp + ")"NOR;
        pic2 = sprintf("    "HIG"(%|4d)航海者 %s"NOR, query("hp"), pic_me);

        write( sprintf("\n       %|8s！    _ _ _ _ _ _ _ _ _ _\n                   "HIY"¤"NOR"                     \\    "HIR"-%d"NOR +
                "\n%s                        %s\n≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈\n\n", temp, damage, pic2,  pic1));
        if ( random(100) > miss ) {
                target_hp -= damage;
                write(HIY"使用" + temp + "对" + query("who_name") + "进行攻击！损害对方" + damage + "。\n"NOR);
        }
        else {
                write(HIY"然而并没有打中" + query("who_name") + "。\n"NOR);
        }
        att_now = "not_ok";
        remove_call_out("target_check_hp");
        call_out("target_check_hp", 1);
        return 1;
}

void target_check_hp()
{
        int exp, pot;
        string msg;
        mapping reward;
        object me = get_me();

        if ( !me ) {
                remove_call_out("del_me");
                call_out("del_me", 1);
                return;
        }
        if ( target_hp < 1 ) {
                addn("sunk_enemy", 1);
                if ( query("who_name") == "吉野号" ) {
                        tell_object(me, "你成功地将日本海军旗舰击沉，完成任务。\n");
                        reward=TASK_D->get_reward(me,5000,3,1000+random(500),query("job/fleet", me));
                        exp = reward["exp_reward"];
                        pot = reward["pot_reward"];
                        addn("combat_exp", exp, me);
                        addn("potential", pot, me);
                        addn("job/jiawu", 1, me);
                        tell_object(me, "你被奖励了" + exp + "点经验值，" + pot + "点潜能。\n");
                        msg="【闲聊】北洋水师(beiyangshuishi)："+query("name", me)+HIC"成功地击沉了日本海军旗舰──吉野号。\n";
                        message("channel:chat", HIC + msg + NOR, users());
                        remove_call_out("del_me");
                        call_out("del_me", 1);
                        return;
                }
                if ( query("sunk_enemy") > 10 ) {
                        tell_object(me, "你成功地击沉数艘敌舰，可以返行了。\n");
                        reward=TASK_D->get_reward(me,1500,3,500+random(500),query("job/jiawu", me));
                        exp = reward["exp_reward"];
                        pot = reward["pot_reward"];
                        addn("combat_exp", exp, me);
                        addn("potential", pot, me);
                        addn("job/jiawu", 1, me);
                        tell_object(me, "你被奖励了" + exp + "点经验值，" + pot + "点潜能。\n");
                        msg="【闲聊】北洋水师(beiyangshuishi)："+query("name", me)+HIC"成功地击沉了日本海军旗舰的攻击。\n";
                        message("channel:chat", HIC + msg + NOR, users());
                        remove_call_out("del_me");
                        call_out("del_me", 1);
                        return;
                }
                game_now = "等待移动命令";
                addn("hp", 1 + (random(5)) );
                if( query("hp") > 120 ) set("hp", 120);
                map();
                write(HIG"\n你打败了 " + query("who_name") + " ！获得了少量的补给。继续出发吧！\n\n"NOR);
                set_temp("haizhan_cond", "ok", me);
                return;
        }
        be_attack();
}
