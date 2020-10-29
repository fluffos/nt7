/*
    ----------------------------------------    暗黑之城    ----------------------------------------------
     ① 1.罗格营地 2.冰冻之原 3.石块旷野 4.黑暗森林 5.黑色荒地 6.外侧回廊 7.监牢一层 8.内侧回廊 9.墓穴二层
     ② 1.鲁高·因 2.地下水道 3.干燥高地 4.死亡之殿 5.遥远绿洲 6.失落城市 7.皇宫监牢 8.庇难之所 9.术士峡谷
     ③ 1.库拉海港 2.蜘蛛森林 3.庞大湿地 4.剥皮丛林 5.库拉上层 6.库拉商场 7.库拉下层 8.崔凡克   9.憎恨囚牢
     ④ 1.群魔堡垒 2.神罚之城 3.火焰之河 4.罗格之岛 5.九龙之塔 6.天囚之城 7.迷雾沼泽 8.格拉瑞特 9.飓风极地
     ⑤ 1.哈洛加斯 2.冰冻高原 3.亚瑞特   4.水晶通道 5.冰河之路 6.痛苦之厅 7.冰冻苔原 8.远古之路 9.要塞二层
     ⑥ 1.特罗巴岛 2.罗巴山脉 3.十二列岛 4.远古员峤 5.失落岱兴 6.玛雅部落 7.雷泽国度 8.东海汤谷 9.荣耀之路
*/

#include <room.h>
#include <ansi.h>
inherit ROOM;
inherit __DIR__"diablo";
#include <eve.h>
#include <hero.h>

mixed *mask;
string display_map(string arg);
int do_drop(object me, object obj);
int do_get(object me, object obj, object env);
int can_visible(int y,int x,int z);
void generate_bandit(string zone);

mapping zone_range(){ return ZONE_RANGE; }
mapping hero() { return HERO; }

mapping add_zone_range(mapping zone)
{
        ZONE_RANGE+=zone;
        return ZONE_RANGE;
}

mapping remove_zone_range(mapping zone)
{

        object *bandit1;
        reset_eval_cost();

        bandit1=filter_array(children(__DIR__"npc/bandit"),(:query("name",$1)==$2:),zone[keys(zone)[0]]["bandit"]);
        if( sizeof(bandit1) ) map_array(bandit1,(:destruct($1):));

        map_delete(ZONE_RANGE,zone);
        return ZONE_RANGE;
}

object *dusers()
{
        object *obs;

        obs = filter_array(users(), (: environment($1)==this_object() :));
        obs = filter_array(obs,(:query("coor/z", $1)==0:));

        return obs;
}

mapping *generate_wall(int x,int y,int z,mapping coor)
{
        string *ks;
        int i,next_flag;
        mapping connect,*walls,*new_wall;

        walls=query("walls");
        //coor=ZONE_RANGE[query("zone")];
        if( !walls ) walls=({});
        new_wall=
        ({
                ([      "x1":x,
                        "x2":x+S_SIZE,
                        "y1":y,
                        "y2":y-L_SIZE,
                        "z1":z+coor["z1"],
                        "z2":z+coor["z2"],
                ]),


                ([      "x1":x,
                        "x2":x+L_SIZE,
                        "y1":y,
                        "y2":y-S_SIZE,
                        "z1":z+coor["z1"],
                        "z2":z+coor["z2"],
                ]),

                ([      "x1":x+S_SIZE,
                        "x2":x+L_SIZE,
                        "y1":y-L_SIZE+S_SIZE,
                        "y2":y-L_SIZE,
                        "z1":z+coor["z1"],
                        "z2":z+coor["z2"],
                ]),

                ([      "x1":x+L_SIZE-S_SIZE,
                        "x2":x+L_SIZE,
                        "y1":y,
                        "y2":y-L_SIZE,
                        "z1":z+coor["z1"],
                        "z2":z+coor["z2"],
                ]),
        });

        walls+=new_wall;
        set("walls",walls);

        return new_wall;
}


mapping query_zonexyz(int x,int y,int z)
{
        int i;
        string desc;
        string *ks;
        mapping coor;

        ks=keys(ZONE_RANGE);

        for( i=0;i<sizeof(ks);i++ )
        {
                coor=ZONE_RANGE[ks[i]];

                if( x>=coor["x1"]&&x<=coor["x2"]&&y>=coor["y2"]&&y<=coor["y1"] )
                        return coor;
        }

        return ([]);
}

mapping query_zone(object ob)
{
        int x,y,z,i;
        string desc;
        string *ks;
        mapping coor;

        ks=keys(ZONE_RANGE);
        x=query("coor/x",ob);
        y=query("coor/y",ob);
        z=query("coor/z",ob);

        for(i=0;i<sizeof(ks);i++)
        {
                coor=ZONE_RANGE[ks[i]];

                if( x>=coor["x1"]&&x<=coor["x2"]&&y>=coor["y2"]&&
                    y<=coor["y1"]&&z<=coor["z1"]&&z>=coor["z2"] )
                        return coor;
        }

        return ([]);
}

string short_desc()
{
        int x,y,z,i;
        string desc;
        string *ks;
        mapping coor;

        ks=keys(ZONE_RANGE);
        x=query("coor/x",this_player());
        y=query("coor/y",this_player());
        z=query("coor/z",this_player());
        for(i=0;i<sizeof(ks);i++)
        {
                coor=ZONE_RANGE[ks[i]];

                if( x>=coor["x1"]&&x<=coor["x2"]&&y>=coor["y2"]&&
                    y<=coor["y1"] &&z>=coor["z1"]&&z<=coor["z2"] )
                        desc=coor["name"];
        }
        if( !desc ) desc="无尽虚空";
        return desc;
}

void create()
{
        int i,j;
        object mine,door;
        mapping *walls;

        walls=DATABASE_D->db_walls();
        if( !walls )
                walls=({
                        ([      "x1":-180,
                                "x2":1000,
                                "y1":180,
                                "y2":100,
                                "z1":0,
                                "z2":0,
                        ]),
                });

        set("walls",walls);
        set("short", HIC+short_desc()+NOR);
        set("long",
HIC"\n                   此处便是暗黑之地。\n\n"NOR
        " 移动指令 "HIY"moving "NOR"<"HIY"方位"NOR"|"HIY"目标"NOR">
        停止移动： "HIY"stopping"NOR"
        回扬州： "HIY"back"NOR"
        显示地图：        "HIY"set eve_map n(9-29)"NOR"
        显示地图分辨率：  "HIY"set eve_step n(建议10-100)"NOR"
        定位地图中心坐标："HIY"set eve_center x(建议自己或者center)"NOR"
 // 屏蔽他人移动、战斗信息："HIY"set combat_message "NOR"<"HIY"1"NOR"|"HIY"2"NOR">
"NOR);
        set("outdoors", "war");
        set("valid_startroom", 1);
        set("no_clean_up",1);
        set("PK_FREE",1);
        set("objects", ([
                //__DIR__"npc/akala": 1,
                __DIR__"obj/door": 1,
                __DIR__"obj/tomb": 1,

        ]) );

        set("coor/x",0);
        set("coor/y",0);
        set("coor/z",0);
        set("map","war");
        set("warroom",1);
        set("no_magic",1);
        set("fight-range",40);
        set("can_vision",80);
        set("reduce_range",40);
        set("max_speed",10);
        set("bandit_number",10);
        set("reset_time",8);
        setup();
        generate_bandit("blood");

        mask = allocate(72);
        for(i=0; i<72; i++)
        {
                mask[i] = allocate(72);
                for(j=0;j<72;j++)
                        mask[i][j]=allocate(20);
        }
}


varargs void generate_bandit(string zone,mapping coor,int z)
{
        object bandit,door,tomb;
        int i,j,length_x,length_y,length_z,step,x,y;

        string *ks;

        if( !coor ) coor=ZONE_RANGE[zone];
        if (!z ) z=coor["z1"];

        ks=keys(coor);
        step=SPREAD_SIZE;
        length_x=coor["x2"]-coor["x1"];
        length_y=coor["y1"]-coor["y2"];

        if( query("generate/"+zone) ) return;

        if( member_array("no_door", ks)==-1 )
                if( !sizeof(filter_array(children(__DIR__"obj/door"),(:query("zone",$1)==$2:),zone)) )//区域没有门时才生成
                {
                        door=new(__DIR__"obj/door");//区域生成传送门
                        set("zone",zone,door);
                        set("no_reset",1,door);
                        set("act",coor["act"],door);
                        door->set_coor();
                        door->move(this_object());
                }
        if( member_array("bandit", ks)==-1 &&//没有怪物的区域设定坟墓
            member_array("no_tomb", ks)==-1 )
                if( !sizeof(filter_array(children(__DIR__"obj/tomb"),(:query("zone",$1)==$2:),zone)) )
                {
                        tomb=new(__DIR__"obj/tomb");
                        set("zone",zone,tomb);
                        set("no_reset",1,tomb);
                        set("act",coor["act"],tomb);
                        tomb->set_coor();
                        tomb->move(this_object());
                }

        if( member_array("boss", ks)!=-1)
                if( !sizeof(filter_array(children(__DIR__"npc/boss"),(:query("zone",$1)==$2:),zone)) )
                {
                        bandit=new(__DIR__"npc/boss");//区域生成BOSS

                        set("zone",zone,bandit);
                        set("skill_level",coor["level"],bandit);
                        set("name",coor["boss"],bandit);
                        set("element",elements(coor["act"]),bandit);
                        x=coor["x1"]+step+(length_x-2*step)*(random(2));
                        y=coor["y2"]+step+(length_y-2*step)*(random(2));
                        set("coor/x",x,bandit);
                        set("coor/y",y,bandit);
                        set("coor/z",z,bandit);
                        set("old_coor/x",x,bandit);
                        set("old_coor/y",y,bandit);
                        set("old_coor/z",z,bandit);
                        set("no_reset",1,bandit);
                        bandit->move(this_object());
                        bandit->setup();
                }

        if( member_array("bandit", ks)!=-1 )
        {
                object *bandit1=filter_array(children(__DIR__"npc/bandit"),(:query("name",$1)==$2:),coor["bandit"]);
                if( sizeof(bandit1) ) map_array(bandit1,(:destruct($1):));

                for(i=0;i<length_x/step;i++)
                        for(j=0;j<length_y/step;j++)
                        {
                                bandit=new(__DIR__"npc/bandit");//区域以步长step生成小怪
                                set("name",coor["bandit"],bandit);
                                set("zone",zone,bandit);
                                set("skill_level",coor["level"],bandit);
                                set("element",elements(coor["act"]),bandit);
                                set("coor/x",coor["x1"]+i*step,bandit);
                                set("coor/y",coor["y2"]+j*step,bandit);
                                set("coor/z",z,bandit);
                                set("old_coor/x",query("coor/x",bandit),bandit);
                                set("old_coor/y",query("coor/y",bandit),bandit);
                                set("old_coor/z",query("coor/z",bandit),bandit);
                                set("no_reset",1,bandit);
                                if( !random(10)&&strsrch(query("name",bandit),"洞穴怪")==-1 ) set("hero_num",random(20),bandit);
                                if( !random(10)&&strsrch(query("name",bandit),"洞穴怪")==-1 ) set("hero_num",random(50),bandit);
                                if( !random(10)&&strsrch(query("name",bandit),"洞穴怪")==-1 ) set("hero_num",random(100),bandit);

                                bandit->setup();
                                bandit->move(this_object());
                                if( bandit->rearch_wall(query("coor/x",bandit),query("coor/y",bandit),query("coor/z",bandit)) )
                                        destruct(bandit);
                        }
        }
        set("generate/"+zone,1);
}

void reset()
{
        int i,j;
        object *bandit1;
        ::reset();

        add("reset_time",-1);
        set("no_clean_up", 1 );
        set("user_num",sizeof(dusers()));
        if( !query("reset_time") )
        {
                //reset_eval_cost();
                bandit1=children(__DIR__"npc/bandit");
                if( sizeof(bandit1) )
                        foreach(object mem in bandit1)
                        {
                                if( strsrch(query("name",mem),"洞穴怪")==-1 )
                                        destruct(mem);
                        }
                bandit1=children(__DIR__"npc/boss");
                if( sizeof(bandit1) )
                        map_array(bandit1,(:destruct($1):));
                delete("generate");
                set("reset_time",8);
                generate_bandit("blood");
                tell_room(this_object(),BLINK+HIG"暗黑城重置了。\n"NOR);
        }
        else if( !query("reset_time")%4 )
        {
                mask = allocate(72);
                for(i=0; i<72; i++)
                {
                        mask[i] = allocate(72);
                        for(j=0;j<72;j++)
                                mask[i][j]=allocate(20);

                }
                tell_room(this_object(),BLINK+HIG"暗黑城又陷入了一片黑暗。\n"NOR);
        }
}

void init()
{
        set("user_num", sizeof(dusers()));
        set("coon/x",query("coon/x"),this_player());
        set("coon/y",query("coon/y"),this_player());
        set("coon/z",query("coon/z"),this_player());

        add_action("do_moving","moving");
        //add_action("do_around","around");
        //add_action("do_driving","driving");
        add_action("do_stopping","stopping");
        add_action("do_perform","perform");
        add_action("do_nothing","exert");
        add_action("do_nothing","conjure");
        add_action("do_cast","cast");
        add_action("do_nothing","curse");
        add_action("do_nothing","mount");
        add_action("do_nothing","qi");
        add_action("do_nothing","usemark");
        add_action("do_nothing","setmark");
        add_action("do_nothing","rideto");
        //add_action("do_nothing","eat");
        add_action("do_nothing","whistle");
        add_action("do_dropping","drop");
        add_action("do_nothing","do");
        //add_action("do_nothing","give");
        //add_action("do_nowield","wield");
        //add_action("do_nowield","unwield");
        add_action("do_move","move");
        //add_action("do_mov","get");
        add_action("display_map","map");
        add_action("do_back","back");
        add_action("do_dismiss","dismiss");
        add_action("do_quit","quit");
}

int do_perform(string arg)
{
        object me;
        me=this_object();

        if( !query("diablo_achieve/"+query("coor/z",me)+"/hero",me) )
        {
                tell_object(me,"你需要打通暗黑城后才可以使用绝招。\n");
                return 1;
        }
        return 0;
}

int do_cast(string arg)
{
        object me;
        me=this_object();

        if( !query("diablo_achieve/"+query("coor/z",me)+"/hero",me))
        {
                tell_object(me,"你需要打通暗黑城后才可以使用绝招。\n");
                return 1;
        }
        return 0;
}

int do_quit(string arg)
{
        object me;
        me=this_object();

        if( this_player()->is_fighting() )
        {
                tell_object(me,"你还在战斗。\n");
                return 1;
        }
        if( query("block_move",this_player()) )
        {
                tell_object(me,"你死了先touch tomb复活。\n");
                return 1;
        }
        delete("coor",me);
        return 0;
}

int do_dismiss(string arg)
{
        mapping employ,hp_left;
        string animal1;
        object me=this_player();

        if( !mapp(employ=query("employ",me)) )
                return notify_fail("你还没有雇佣兵，怎么解雇。\n");

        foreach(string animal in keys(HERO))
                if( arg==HERO[animal]["name"] ) animal1=animal ;

        if( !animal1 ) return notify_fail("没有这种雇佣兵种类啊。\n");

        if( member_array(animal1,keys(employ))==-1 )
                return notify_fail("你没有这种雇佣兵，怎么解雇。\n");

        //map_delete(employ,animal1);
        delete("employ/"+animal1,me);
        if( mapp(hp_left=query("hp_left",me)) )
        {
                map_delete(hp_left,animal1);
                set("hp_left",hp_left,me);
        }
        tell_object(me,"你解散了"+HERO[animal1]["name"]+"。\n");
        return 1;
}

int do_back(string arg)
{
        object obj,me;
        string dest;

        me=this_player();
        dest="/d/city/guangchang";
        if( !(obj = load_object(dest)) )
        {
                tell_object(me,"无法移动。\n");
                return 1;
        }

        if( query("coor/z",me) )
        {
                tell_object(me,"你可能在洞穴里，需要找到出口。\n");
                return 1;
        }

        if( me->is_fighting() )
        {
                tell_object(me,"你还在战斗。\n");
                return 1;
        }

        if( query("block_move",me) )
        {
                tell_object(me,"你死了先touch tomb复活。\n");
                return 1;
        }

        if( sizeof(keys(query_zone(me))) )
                if( member_array("bandit",keys(query_zone(this_player())))!=-1 )
                {
                        delete("coor",me);
                        tell_object(me,"你回到了罗格营地。\n");
                        return 1;
                }

        me->move(obj);
        delete_temp("moving_target",me);
        delete_temp("moving",me);
        return 1;
}

int do_nowield(string arg)
{
        tell_object(this_player(),"只有在基地才能上下战车，你已经到了战场，早干啥去了。\n");
        return 1;
}

int do_dropping(string arg)
{
        object obj, *inv, obj2;
        int i, amount;
        object me;
        string item;
        mixed no_drop;

        me=this_player();
        if( !arg ) {
                write("你要丢弃什麽东西？\n");
                return 1;
        }
        if( query_temp("timer/big_cmd",me)+2 > time()) {
                write("此命令比较耗费系统资源，每两秒只能执行一次。\n");
                return 1;
        }
        if( !wizardp(me))
                set_temp("timer/big_cmd",time(),me);

        if( arg=="all" ) {
                inv = all_inventory(me);
                for(i=0; i<sizeof(inv); i++) {
                        do_drop(me, inv[i]);
                }
                write("Ok.\n");
                return 1;
        }

        if( sscanf(arg, "%d %s", amount, item)==2 ) {
                if( !objectp(obj = present(item, me)) ) {
                        write("你身上没有这样东西。\n");
                        return 1;
                }
                if( stringp(query("no_drop",obj)) ) {
                        write((string)query("no_drop",obj));
                        return 1;
                }
                if( !obj->query_amount() ) {
                        write(obj->name() + "不能被分开丢弃。\n");
                        return 1;
                }
                if( amount < 1 ) {
                        write("东西的数量至少是一个。\n");
                        return 1;
                }
                if( no_drop = query("no_drop",obj) ) {
                        write(stringp(no_drop) ? no_drop : "这样东西不能随意丢弃。\n");
                        return 1;
                }
                if( amount > obj->query_amount() ) {
                        write("你没有那麽多的" + obj->name() + "。\n");
                        return 1;
                }
                else if( amount == (int)obj->query_amount() )
                        return do_drop(me, obj);
                else {
                        obj->set_amount( (int)obj->query_amount() - amount );
                        obj2 = new(base_name(obj));
                        obj2->set_amount(amount);
                        return do_drop(me, obj2);
                }
        }

        if( !objectp(obj = present(arg, me)) ) {
                write("你身上没有这样东西。\n");
                return 1;
        }
        return do_drop(me, obj);
}

int do_drop(object me, object obj)
{
        object gui;
        mixed no_drop;

        if( no_drop = query("no_drop",obj) )
                return notify_fail( stringp(no_drop) ? no_drop : "这样东西不能随意丢弃。\n");

        gui=new("/d/war/obj/gui");
        set("coor/x",query("coor/x",me),gui);
        set("coor/y",query("coor/y",me),gui);
        set("coor/z",query("coor/z",me),gui);
        gui->move(environment(me));
        if( obj->move(gui) ) {
                if( obj->is_character() )
                        message_vision("$N将$n从背上放了下来，放在临时货柜里。\n", me, obj);
                else {
                        message_vision( sprintf("$N丢下%s放到一个新的临时货柜里。\n", obj->short() ),me);
                        me->save();
                }
                return 1;
        }
        destruct(gui);
        return 0;
}

int do_nothing(string arg)
{
        tell_object(this_player(),"这里是古战场，禁止使用绝招。\n");
        return 1;
}

int do_driving(string arg)
{
        object me;
        string dest;
        int distance,distance_x,distance_y,distance_z,max_speed,max_driving;
        object obj;

        me = this_player();
        max_speed=query_temp("apply/max_speed",me);
        max_driving=query_temp("apply/max_driving",me);

        if( !max_speed ) max_speed=187;
        if( !max_driving ) max_driving=1000000;
        if( !arg ) return notify_fail("你要往哪里去？\n");
        if( me->over_encumbranced() )
                return notify_fail("你的负荷过重，动弹不得。\n");
        if( (!obj=present(arg,environment(me)))&&(!obj=present(arg,me)) )
                return notify_fail("没有这个地方？\n");

        if( me->distance(obj)<250000 )
        {
                return notify_fail("你距离"+query("name",obj)+"太近了,请使用moving,当前距离"+me->distance(obj)+"米。\n");
        }

        if( query_temp("moving",me)<max_speed*80/100 )
        {
                return notify_fail("你的速度还不够。（要达到战车最大速度的８０％才可以开始强行\n");
        }

        if( query_temp("driving_target",me) )
                return notify_fail("你正在强行状态。\n");

        set_temp("driving",query_temp("moving",me),me);
        set_temp("acc_driving",max_driving/5,me);
        set_temp("driving_target",obj,me);
        delete_temp("direction",me);
        delete_temp("moving_target",me);
        delete_temp("arounding_target",me);
        write("你开始向"+query("name",obj)+"强行。\n");
        return 1;
}

int do_moving(string arg)
{
        object me = this_player();
        string dest;
        int distance,distance_x,distance_y,distance_z,max_speed;
        object obj;
        string *directions = ({ "east", "south",  "west", "north","se", "sw", "ne",  "nw", "up","down" });

        max_speed=query_temp("apply/max_speed",me);
        if( query("block_move",me) )
                return notify_fail("你还没复活，请touch tomb复活。\n");

        if( me->query_busy() )
                return notify_fail("你正忙着呢，再等一会。\n");
        if( me->over_encumbranced() )
                return notify_fail("你的负荷过重，动弹不得。\n");

        if( !max_speed ) max_speed=query("max_speed");
        if( !arg ) return notify_fail("你要往哪里移动\n");
        if( arg=="down"||arg=="up" )
                return notify_fail("就你这水平还想上天入地？\n");
        if( query_temp("driving_target",me) )
                return notify_fail("你正在强行状态，呆会再试。\n");

        if( member_array(arg, directions)==-1 )
        {
                if( !obj=present(arg,environment(me)) )
                        obj=present(arg,me);
                if( !obj ) return notify_fail("你只能向目标或者方位移动。\n");
                if( objectp(obj) ) {
                        delete_temp("direction",me);
                        distance=me->distance(obj);
                        if( distance<10 ) {
                                set("coor/x",query("coor/x",obj),me);
                                set("coor/y",query("coor/y",obj),me);
                                set("coor/z",query("coor/z",obj),me);
                                return notify_fail("你已经抵达"+query("name",obj)+"了。\n");
                        }

                        set_temp("moving",5,me);
                        set_temp("acc_speed",max_speed/5,me);

                        set_temp("moving_target",obj,me);
                        delete_temp("arounding_target",me);
                        write("你开始向"+query("name",obj)+"移动。\n");
                        return 1;
                }
        }

        if( (member_array(arg, directions)!=-1)&&(!objectp(obj)) )
        {
                set_temp("direction",arg,me);
                delete_temp("moving_target",me);
                delete_temp("arounding_target",me);
                set_temp("moving",5,me);
                set_temp("acc_speed",max_speed/5,me);
                write("你开始向"+arg+"方向移动。\n");
                return 1;
        }
}

int do_stopping(string arg)
{
        object me = this_player();

        if( !query_temp("moving",me) ) return notify_fail("你没有在移动状态。\n");
        if( query_temp("driving",me) ) return notify_fail("你正在强行状态，稍后再试。\n");
        delete_temp("speed_x",me);
        delete_temp("speed_y",me);
        delete_temp("speed_z",me);
        delete_temp("moving",me);
        delete_temp("moving_target",me);
        delete_temp("arounding_target",me);
        delete_temp("arounding",me);
        tell_object(me,"你停止移动。\n");
        return 1;
}

int alternative_die(object me)
{
        object ob,weapon;
        object *tomb,*inv;
        int i;
        string act,msg;
        mapping mail;


        weapon=query_temp("weapon",me);


        if( userp(me) )
        {
                me->clear_all_condition();
                me->remove_all_killer();
                if( query_temp("moving",me) ) set_temp("moving",0,me);
                if( query_temp("moving_target",me) ) delete_temp("moving_target",me);
                if( query_temp("direction",me) ) delete_temp("direction",me);

                all_inventory(environment(me))->remove_killer(me);

                //BUFF_D->debuff(me, "all");
                me->clear_all_condition();
                delete_temp("block_msg/all",me);
                ob = query_temp("last_damage_from",me);
                act=query_zone(me)["act"];
                if( !act ) act="act1";
                if( act=="act2"&&!query("generate/rogoin") ) generate_bandit("rogoin");
                if( act=="act3"&&!query("generate/dock") ) generate_bandit("dock");
                if( act=="act4"&&!query("generate/bastion") ) generate_bandit("bastion");
                if( act=="act5"&&!query("generate/harlow") ) generate_bandit("harlow");
                if( act=="act6"&&!query("generate/terob") ) generate_bandit("terob");

                set("qi",100,me);
                set("jing",100,me);
                me->start_busy(5);
                set("block_move",1,me);


                if( objectp(ob) ) {
                        message_vision (RED"\n$N在暗黑城的"+query_zone(me)["name"]+"被$n杀死了！\n\n"NOR,me,ob);
                        set_temp("die_reason", "被"+ob->name(1)+HIY"捏碎了蛋,死掉了！",me);
                        tell_object(me,"你被传送到坟墓附近，请touch tomb复活。\n");

                } else {
                        message_vision (RED"\n$N在暗黑城的"+query_zone(me)["name"]+"被$n杀死了！\n\n"NOR,me);
                        set_temp("die_reason", "被捏碎了蛋,死掉了！",me);
                        tell_object(me,"你被传送到坟墓附近，请touch tomb复活。\n");

                }
                tomb=filter_array(children("/d/war/obj/tomb"),(: //environment($1) == this_object() &&
                        query("act",$1)==$2:),act);

                if( sizeof(tomb) )
                        set("coor",query("coor",tomb[0]),me);
                return 1;
        } else {

                if( objectp(ob = query_temp("last_damage_from",me))&&userp(ob) && query("eve_reward",me))
                {
                        addn("isk",query("eve_reward",me),ob);
                        tell_object(ob,"你获得了"+query("eve_reward",me)+"ISK的赏金");
                }
        }
        return 0;
}

int do_around(string arg)
{
        object me = this_player();
        string dest,target;
        int distance,distance_x,distance_y,distance_z,max_speed,number;
        object obj;
        string *directions = ({ "east", "south",  "west", "north","se", "sw", "ne",  "nw", "up","down" });

        max_speed=query_temp("apply/max_speed",me);
        if( me->over_encumbranced() )
                return notify_fail("你的负荷过重，动弹不得。\n");
        if( !max_speed ) max_speed=175;
        if( !arg ) return notify_fail("你要环绕哪个目标\n");

        if( query_temp("driving_target",me) )  return notify_fail("你正在强行状态，呆会再试。\n");
        if( !obj=present(arg,environment(me)) )
                obj=present(arg,me);
        if( !objectp(obj) )
                return notify_fail("你只能环绕目标。\n");

        if( me->distance(obj)<500 ) return notify_fail("环绕至少500米。\n");
        if( me->distance(obj)>30000 ) return notify_fail("环绕最多30km。\n");

        delete_temp("direction",me);
        distance=me->distance(obj);
        set_temp("moving",1,me);
        set_temp("acc_speed",max_speed/5,me);
        delete_temp("moving_target",me);
        set_temp("arounding_target",obj,me);
        set_temp("arounding",number,me);
        write("你开始以半径"+me->distance(obj)+"向"+query("name",obj)+"环绕。\n");
        message_vision(YEL"\n$N开始以半径"+me->distance(obj)+"环绕$n。\n",me,obj);
        return 1;
}

int do_move(string arg)
{
        object me,target;
        string from;
        object obj, obj2,*inv, env,item;
        int i,amount;

        me=this_player();
        if( !arg ) return notify_fail("你要搬什么?\n");
        if( sscanf(arg, "%s from gui%s", arg, from)!=2 )
                return notify_fail("指令格式：move <物品ID> from gui+<编号>\n");

        from = "gui" + from;
        env = present(from, environment(me));
        if( !env|| !env->query("is_gui") )  return 0;

        target = query_temp("weapon",me);
        if( !target || query("skill_type",target)!="tank" ) {
                tell_object(me, "你没有操作战车，无法激活货柜仓。\n");
                return 1;
        }
        if( me->distance(env)>5000 ) {
                tell_object(me, "你距离货柜太远了，无法操作货柜（至少5000米内）。\n");
                return 1;
        }
        if( sscanf(arg, "%d %s", amount, item)==2 ) {
                if( !objectp(obj = present(item, env)) )
                        return notify_fail("货柜里没有这样东西。\n");
                if( !obj->query_amount() )
                        return notify_fail( obj->name() + "不能被分开拿走。\n");
                if( amount < 1 )
                        return notify_fail("东西的个数至少是一个。\n");
                if( amount > obj->query_amount() ) {
                        return notify_fail("货柜里没有那麽多的" + obj->name() + "。\n");
                } else if(amount == (int)obj->query_amount()) {
                        return do_get(me, obj, env);
                } else {
                        obj->set_amount( (int)obj->query_amount() - amount );
                        obj2 = new(base_name(obj));
                        obj2->set_amount(amount);
                        obj2->set_name(query("name",obj),obj->parse_command_id_list());
                        set("long",query("long",obj),obj2);
                        set("unit",query("unit",obj),obj2);
                        obj2->move(me);
                        if( query("skill_type",env)=="tank" ) //设置战车
                                switch(query("material",obj2))
                                {
                                case "mine":
                                        if( query("used_mine_volumn",env)<query("capacity",obj2)*obj2->query_amount())
                                        {
                                                addn("used_volumn",-query("capacity",obj2)*obj2->query_amount()+query("used_mine_volumn",env),env);
                                                set("used_mine_volumn",0,env);
                                        } else
                                                addn("used_mine_volumn",-query("capacity",obj2)*obj2->query_amount(),env);
                                        break;
                                case "ore":
                                        if( query("used_ore_volumn",env)<query("capacity",obj2)*obj2->query_amount())
                                        {
                                                addn("used_volumn",-query("capacity",obj2)*obj2->query_amount()+query("used_ore_volumn",env),env);
                                                set("used_ore_volumn",0,env);
                                        } else
                                                addn("used_ore_volumn",-query("capacity",obj2)*obj2->query_amount(),env);
                                        break;
                                default:
                                        addn("used_volumn",-query("capacity",obj2)*obj2->query_amount(),env);
                                        break;
                                }

                        obj2->move(environment(me));
                        set("coor/x",query("coor/x",me),obj2);
                        set("coor/y",query("coor/y",me),obj2);
                        set("coor/z",query("coor/z",me),obj2);
                        // Counting precise amount costs more time.
                        if( me->is_fighting() ) me->start_busy(3);
                        return do_get(me, obj2, env);
                }
        }

        if( arg=="all" ) {
                inv = all_inventory(env);
                if( !sizeof(inv) )
                        return notify_fail("货柜里面没有任何东西。\n");
                for(i=0; i<sizeof(inv); i++) {
                        if( (inv[i]->is_character() && !query("yes_carry",inv[i])) || query("no_get",inv[i]) ||
                                query("lore",inv[i])) continue;
                        do_get(me, inv[i], env);
                }
                write("Ok。\n");
                return 1;
        }
        if( !objectp(obj = present(arg, env)) || (living(obj) && !(int)query("yes_carry",obj)) )
                return notify_fail("货柜里没有这样东西。\n");
        if( query("no_get",obj) )
                return notify_fail("这个东西拿不起来。\n");

        return do_get(me, obj, env);
}

int do_get(object me, object obj, object env)
{
        object *inv;
        object target;
        string prep, str;

        target = me->query_temp("weapon");
        if( !obj ) return notify_fail("没有这个东西。\n");
        if( !target ) return notify_fail("你没有操作战车，无法激活货柜仓。\n");
        if( query("skill_type",target)!="tank") return notify_fail("你没有操作战车，无法激活货柜仓。\b");

        if( obj->is_character()  && living(obj) ) {
                return notify_fail("你不能装活物。\n");
        } else {
                if( query("no_get",obj) ) return 0;
        }

        str = obj->short();
        if( obj->move(target) ) {
                if( !query("got_time",obj))
                        set("got_time",time(),obj);
                if( query("value",obj)>= 1000
                        && !query("money_id",obj)
                        && query("material",obj)!="herb")
                                log_file("money_item", sprintf("%s worth %d.\n",base_name(obj) ,query("value",obj)));

                if( (int)query("no_transfer",obj)){
                        set("no_get",1,obj);
                        set("no_drop",1,obj);
                }

                if( me->is_fighting() )
                        me->start_busy(1);
                if( obj->is_character()  && !query("yes_carry",obj))
                        message_vision( "$N将$n扶了起来背在背上。\n", me, obj );
                else {
                        switch( query("prep",env) ) {
                                case "on":
                                        prep = "从" + env->name() + "上拿起";
                                        break;
                                case "under":
                                        prep = "从" + env->name() + "下拿出";
                                        break;
                                case "behind":
                                        prep = "从" + env->name() + "后拿出";
                                        break;
                                case "inside":
                                        prep = "从" + env->name() + "中拿出";
                                        break;
                                default:
                                        prep = "从" + env->name() + "中拿出";
                                        break;
                        }
                        message_vision( sprintf("$N%s" + str + ",放进" + query("name",target) + "的货柜仓。\n", prep, query("unit",obj)), me, obj );
                }
                inv = all_inventory(env);
                if( !sizeof(inv) )
                        env->destroy();
                return 1;
        }
        else return 0;
}

string display_map(string arg)
{
        object *inv,obj,me;
        int m, n, length, ks,temp;
        int max_x, max_y, min_x, min_y, length_x, length_y, i, j, k, h, type, x, y, x1, y1, x2, y2, z1, z2;
        mapping *wall;
        mixed *xy;
        string name;
        string msg = "\n";
        me=this_player();

        if( !arg||sscanf(arg,"%d %d %s",length,n,name)!=3 )
        {       msg="地图查看格式为map 步长，地图大小，中心物体\n";
                write(msg);
                return msg;
        }

       inv = filter_array(all_inventory(this_object()),(:query("coor/z",$1)==query("coor/z",$(me)):));

        obj = present(name, this_object());

        for( i=0; i<sizeof(inv); i++ ) {
                if( query("coor/x",inv[i])>max_x ) max_x = query("coor/x",inv[i]);
                if( query("coor/y",inv[i])>max_y ) max_y = query("coor/y",inv[i]);
                if( query("coor/x",inv[i])<min_x ) min_x = query("coor/x",inv[i]);
                if( query("coor/y",inv[i])<min_y ) min_y = query("coor/y",inv[i]);

                if( length )
                {
                        if( objectp(obj) ) {
                                max_x=query("coor/x",obj)+length*n/2;max_y=query("coor/y",obj)+length*n/2;
                                min_x=query("coor/x",obj)-length*n/2;min_y=query("coor/y",obj)-length*n/2;
                        }
                }
                length_x = max_x - min_x;       if( !length_x ) length_x=5*length;
                length_y = max_y - min_y;       if( !length_y ) length_y=5*length;
        }

        xy = allocate(n);
        for( i=0; i<n; i++ ) xy[i] = allocate(n);

        wall=query("walls");
        ks=sizeof(wall);
        if( ks )

        for(k=0;k<ks;k++)//每个墙壁进行标记
        {
                int x_1,x_2,y_1,y_2;
                x1=wall[k]["x1"];//X小
                x2=wall[k]["x2"];//X大
                y1=wall[k]["y1"];//Y大
                y2=wall[k]["y2"];//Y小
                z1=wall[k]["z1"];
                z2=wall[k]["z2"];
                x_1=wall[k]["x_1"];//X小缺口1
                x_2=wall[k]["x_2"];//X大缺口2
                y_1=wall[k]["y_1"];//Y大缺口1
                y_2=wall[k]["y_2"];//Y小缺口2
                if( y2<min_y) y2=min_y;
                if( y1>max_y) y1=max_y;
                if( x1<min_x) x1=min_x;
                if( x2>max_x) x2=max_x;
                if( x_1<x1) x_1=x1;
                if( x_2>x2) x_2=x2;
                if( y_2<y2) y_2=y2;
                if( y_1>y1) y_1=y1;
                if( query("coor/z",me)<z1||query("coor/z",me)>z2 ) continue;//玩家视野在墙内

                for(j=(max_y-y1)*(n-1)/length_y;j<(max_y-y2)*(n-1)/length_y;j++)
                for(i=(x1-min_x)*(n-1)/length_x;i<=(x2-min_x)*(n-1)/length_x;i++)
                {
                        //if(!can_visible(max_y-j*length_y/(n-1),min_x+i*length_x/(n-1))) continue;
                        if( ((x_2-x_1)>0&&i>=(x_1-min_x)*(n-1)/length_x&&i<=(x_2-min_x)*(n-1)/length_x)||// continue;
                                ((y_1-y_2)>0&&j>=(max_y-y_1)*(n-1)/length_y&&j<=(max_y-y_2)*(n-1)/length_y) ) continue;
                        if( i>n-1) continue;
                        if (j>n-1) continue;
                        xy[j][i] = "■";
                }
        }

        for(i=0; i<sizeof(inv); i++) {
                if( query("coor/x",inv[i])<min_x||query("coor/x",inv[i])>max_x||
                    query("coor/y",inv[i])<min_y||query("coor/y",inv[i])>max_y )
                        continue;
                if( !can_visible(query("coor/y",inv[i]),query("coor/x",inv[i]),query("coor/z",inv[i])) ) continue;

                if( inv[i]==me ) type = 1;
                else if( query("id",inv[i])=="station") type = 99;
                else if( query("boss",inv[i])) type = 4;
                else if( query("attitude",inv[i])=="aggressive") type=2;
                else if( inv[i]->is_character()) type=3;
                else if( query("door",inv[i])) type=11;
                else if( query("tomb",inv[i])) type=12;
                else if( query("startdoor",inv[i])) type=7;
                else if( query("cave",inv[i])) type=13;
                else if( query("zone",inv[i])) type=6;
                else type = 5;

                if( query("owner_id",inv[i])==me ) type+=1000;
                if( query("hero_num",inv[i])) type+=2000;
                if( !xy[(max_y-query("coor/y",inv[i]))*(n-1)/length_y][(query("coor/x",inv[i])-min_x)*(n-1)/length_x] )
                        xy[(max_y-query("coor/y",inv[i]))*(n-1)/length_y][(query("coor/x",inv[i])-min_x)*(n-1)/length_x] = type;

        }
        //上面是对房间中的obj 进行分类标记

        for(j=0;j<n;j++)
                for(i=0;i<n;i++)
                {
                        //if(wizardp(me)&&me->query("env/vision_bug")) continue;

                        if( !can_visible (max_y-j*length_y/(n-1),min_x+i*length_x/(n-1),query("coor/z",me)))
                                if( xy[j][i]!="■"&&(xy[j][i]!=1) ) xy[j][i] = "# ";
                }


        //上面对房间的墙壁标记

        write(FRELINE(0, 80));
        write(SETDISPLAY(1, 88) + "┏");
        for(k=0;k<n/2;k++)
                write("--");
        write("北");
        for(k=0;k<n/2;k++)
                write("--");
        write("┓\n");
        for(i=n-1; i>=0; i--) {
                msg="";
                for(j=0; j<n; j++) {
                        //if(xy[i][j]&&sscanf(xy[i][j],"%d",temp))
                        /*
                        temp=xy[i][j];
                        if(intp(temp)&&temp>1000) {
                                //write("test"+temp);
                                msg=HIM+msg;xy[i][j]=temp-1000;
                        }
                        */
                        if( xy[i][j]==1) msg += "◆"NOR;
                        else if( xy[i][j]==99) msg += "★"NOR;
                        else if( xy[i][j]==13) msg += HIG"⊙"NOR;
                        else if( xy[i][j]==1013) msg += HIM"⊙"NOR;
                        else if( xy[i][j]==4) msg += HIR"★"NOR;
                        else if( xy[i][j]==2) msg += HIR"* "NOR;
                        else if( xy[i][j]==3) msg += HIG"* "NOR;
                        else if( xy[i][j]==1003) msg += HIM"* "NOR;
                        else if( xy[i][j]==2003) msg += HIW"* "NOR;
                        else if( xy[i][j]==5) msg += HIG"．"NOR;
                        else if( xy[i][j]==7) msg += HIG"ｏ"NOR;
                        else if( xy[i][j]==11) msg += HIG"ｏ"NOR;
                        else if( xy[i][j]==12) msg += HIG"▲"NOR;
                        else if( xy[i][j]==6) msg += "▲"NOR;//"▲";
                        else if( xy[i][j] == "■") msg+=HIY"■"NOR;
                        else if( xy[i][j] == "# ") msg+=HIY"# "NOR;
                        else msg += "　";

                }
                write(SAVEC);
                k=2+i;
                h=n*2+90;
                if(k==(n+1)/2) write(SETDISPLAY(k       , 88) + "西"+msg+SETDISPLAY(k,h)+ "东");
                else write(SETDISPLAY(k , 88) + "┃"+msg+SETDISPLAY(k, h)+ "┃");
                write(REST);
        }
        h=n+1;
        write(SETDISPLAY(h, 88) + "┗");
        for(k=0;k<n/2;k++)
                write("--");
        write("南");
        for(k=0;k<n/2;k++)
                write("--");
        write("┛\n");
        h=n+2;
        write(SETDISPLAY(h, 88));

        for(k=0;k<n/2;k++)
                write("  ");
        write("比例尺--="+length+"\n");
        write(TOBOT(200));

        return msg;
}

void set_visible(object user)
{
        int x,y,z,a;

        x=query("coor/x",user);
        y=query("coor/y",user);
        z=query("coor/z",user);
        if( x>1900 || x<-3800 || y>3100 || y<-2500 ) return 0;
        a=z/10000;
        mask[(y+2500)/80][(x+3800)/80][a]=1;
}

int can_visible(int y,int x,int z)
{
        object me=this_player();
        int a=z/10000;

        if( x>1900 || x<-3800 || y>3100 || y<-2500) return 0;
        if( wizardp(me)&&query("env/vision_bug",me)) return 1;

        if( member_array("bandit",keys(query_zonexyz(x,y,z)))==-1&&a==0) return 1;

        return mask[(y+2500)/80][(x+3800)/80][a];
}

void test_visible()
{       int i,j;
        string msg;

        msg="test";
        for(i=0;i<24;i++)
                for(j=0;j<22;j++)
                {
                        write("i:"+i+"j:"+j);
                        msg+=mask[i][j];
                }
        msg+="\n";
        write(msg);
}
