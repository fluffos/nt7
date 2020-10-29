// This program is a part of NITAN MudLIB 
// redl 2013/9
#include <ansi.h> 
#include <room.h>

inherit ROOM;

#define FILEPATH "/u/redl/teleport/"

int clean_up() { return 1;}

mapping *sign = ({
        ([      "file"          :       FILEPATH "tower",       
                "loop"          :       FILEPATH,                               //持续支付时，检查房间范围
                "val"           :       50000                                   
        ]),
        ([      "file"          :       FILEPATH "qiulao",      
                "loop"          :       FILEPATH,
                "val"           :       10000                                   
        ]),
        ([      "file"          :       FILEPATH "tiangong",    
                "loop"          :       FILEPATH,
                "val"           :       30000                                   
        ]),
        ([      "file"          :       FILEPATH "shike",       
                "loop"          :       FILEPATH,
                "val"           :       650000                                   
        ]),
        ([      "file"          :       FILEPATH "baodu",       
                "val"           :       90000000                                        
        ]),
              ([      "file"          :       FILEPATH "lankeshan",        
                      "val"           :       1000000                                                     ]), 
        ([      "file"          :       FILEPATH "huaguo",       
                "loop"          :       FILEPATH,
                "val"           :       10000000                                        
        ]),
       ([      "file"          :       FILEPATH "18niuren",       
                "loop"          :       FILEPATH,
                "val"           :       10000000                                        
        ]),
        ([      "file"          :       FILEPATH "ailao",       
                "val"           :       1000000000                                        
        ]),
        ([      "file"          :       FILEPATH "buzhoushanjiao",       
                "val"           :       10000                                        
        ]),
        ([      "file"          :       "/d/pk/entry",  
                "val"           :       500000                                  
        ]),
});


string look_kong(object me)
{
        string msg;
        int j = 0;
        int i = -1;

        msg = CYN
"孔旁边有几行字：\n"
"  此阵名曰『巧云飞星阵』，它可以带你穿梭到神秘的地方。\n"
"  但需要花费财物来维持它的能量，指令：<put 数量 货币>\n" NOR;  
        while(i++<sizeof(sign)-1){
                if (sign[i]["short"]) {
                        msg += sprintf(" %-28s",  sign[i]["exit"] + ":" + sign[i]["short"] + "("+ chinese_number(sign[i]["val"]/10000) + "金·" + (sign[i]["loop"]? "维持":"进入") +")");
                        j ++;
                        if (j>1) {
                                msg += "\n";
                                j = 0;
                        }
                }
        }
        if (j!=0) msg += "\n";
        
        return msg;
}

void create_exit()
{
        object ob;
        int i = -1;
        int k = 1;
        
        while(i++<sizeof(sign)-1){
                if (sign[i]["file"]) {
                        ob = load_object(sign[i]["file"]);
                        if (objectp(ob)){
                                sign[i] += (["short" : query("short", ob)]);
                                sign[i] += (["exit" : sprintf("%d", k)]);
                                k++;
                                set("exits/" + sign[i]["exit"], sign[i]["file"]);
                        }
                }
        }
}

int do_put(string arg)
{
        object me;
        object ob;
        object nob;
        object *inv;
        string my_id, units;
        int amount;
        int value;
        int max_count;
        int i;
        mixed ns;

        if( !arg )
        {
                        write(NOR "你要把什么投进去？\n" NOR);
                        return 1;
        }

        me = this_player();

                if ((time() - query_temp("teleportroom/put_time", me)) < 6) 
        {
                        write(NOR "你这样反反覆覆算什么，等一会儿再投吧。\n" NOR);
                        return 1;
        }

        if(!interactive(me) || !playerp(me) || me->is_busy()) {
                        write(NOR "你正忙着呢。\n" NOR);
                        return 1;
        }
                
        if( sscanf(arg, "%d %s", amount, arg) != 2 )
                // not indicate the amount of the goods
                amount = 1;

        if( amount < 1 )
        {
                write(NOR "你到底想投多少呢？\n" NOR);
                return 1;
        }
        
        ob = present(arg, me);
        if( !ob )
        {
                inv = all_inventory(me);
                for( i = 0; i < sizeof(inv); i++ )
                {
                        if( filter_color(inv[i]->name(1)) == arg )
                        {
                                ob = inv[i];
                                break;
                        }
                }
        }

        if ( !objectp(ob) )
        {
                write("你身上没有这种东西啊！\n");
                return 1;
        }

        if (!query("money_id", ob))
        {
                write(NOR "在这里只能投钱哦！\n" NOR);
                return 1;
        }
        
      max_count = ob->query_amount();
        if( !max_count )
        {
                // not combined object
                if( amount > 1 )
                {
                        write(NOR + "这" + ob->name() + NOR + "是什么东西？\n" + NOR);
                        return 1;
                }
                max_count = 1;
        } else
        {
                // is combined object
                if( amount > max_count )
                {
                        write(NOR + "你身上没有这么多" + ob->name() + NOR + "。\n" + NOR);
                        return 1;
                }
        }
        
                value = query("base_value", ob) * amount;
                
        if( value < 1000000 )
        {
                write(NOR "你连一百两黄金都拿不出来？这也太寒酸了点吧...\n" NOR);
                return 1;
        }
                
                set_temp("teleportroom/put_value", value, me);
                set_temp("teleportroom/put_time", time(), me);

        units = query("base_unit", ob);
        if (!units) units = query("unit", ob);
        if (!units) units = "个";
                
        message_vision(append_color(CYN + "$N掏出" + chinese_number(amount) + units + ob->name() + CYN + "走过去，机关人迎上前拿过，转身往孔里投了些能量石。\n" + NOR, CYN), me);

                if( max_count == amount ) {
                        destruct(ob);
                }
                else
                {
                        ob->add_amount(-amount);
                }
                
        return 1;
}


int do_look(string arg)
{
        object me = this_player();
        //if ( arg && sscanf(arg, "%*d") ) {
        if ( arg && arg!="south" && arg!="southeast" && query("exits/" + arg) && wiz_level(me) < 5 ) {
                        tell_object(me, NOR "你凝聚目力望过去，却只见浑沌的玄奥气象。\n" NOR);
                        return -1;
        }
        return 0;
}

int init() 
{ 
        object me = this_player();
        if (!interactive(me) || !playerp(me)) return 1;
        add_action("do_look", "look");
        add_action("do_put","put"); 
        if (wiz_level(me) > 5) {
                add_action("do_stop", "stop");
        }
        return 1;
} 

int do_tell_val(object me)
{
        tell_object(me, sprintf(HIG "巧云飞星阵：你储蓄的能量还余(%d)点。\n\n" NOR, query_temp("teleportroom/put_value", me)/10000)); 
        return 1;
}

int do_tell_back(object me)
{
        //tell_object(me, sprintf(HIG "\n天边一股虚弱的能量束缚住了你..\n\n" NOR)); 
        message_vision(append_color(NOR + YEL + "\n天边一股虚弱的能量束缚住了$N..\n\n" + NOR, YEL), me);
        me->move(this_object());
        //tell_object(me, sprintf(HIG "天旋地转中，你头晕目眩地被拉回了法阵。\n\n" NOR)); 
        message_vision(append_color(NOR + YEL + "天旋地转中，$N头晕目眩地被拉回了法阵。\n\n" + NOR, YEL), me);
        return 1;
}

int is_area(mapping my)
{
        object me = my["ob"];
        
        if ( !objectp(me) || 
                !playerp(me) ||
                !interactive(me) ||
                !environment(me) ||
                !objectp(environment(me)) || 
                base_name(environment(me))==base_name(this_object()) ) return 0;
        if ( !sscanf(base_name(environment(me)), sprintf("%s", my["path"]) + "%*s") ) return 0;
        
        if (query_temp("teleportroom/put_value", me) < my["cost"] && time()-my["time"] > 59) {
                do_tell_back(me);
                return -1;
        }
        
        if (time()-my["time"] > 59) {
                addn_temp("teleportroom/put_value", -my["cost"], me);
                do_tell_val(me);
                return 1;
        }
        
        return 2;
}

int check_teleroom()
{
        mapping usrs;
        string *ks;
        int i, count;
        
        remove_call_out("check_teleroom");
        usrs = query("tele_users");
        if (sizeof(usrs)) {
                ks = keys(usrs);
                for(count=sizeof(ks); count > 0; count--)
                {
                        //tell_object(find_player("redl"), sprintf("%s\n", ks[count-1])); 
                        switch ( is_area(query("tele_users/" + ks[count-1])) ) {
                                case -1 :
                                case 0 :
                                        delete("tele_users/" + ks[count-1]);
                                        break;
                                case 1 : 
                                        set("tele_users/" + ks[count-1] + "/time", time());
                                        break;
                                default :
                                        break;
                        }
                }
        }
        
        call_out("check_teleroom", 10);
}

int do_stop()//先清场，再改编
{
        mapping usrs;
        string *ks;
        int i, count;
        object ob;
        object me = this_player();
        
        if (query("do_stop")) {
                delete("do_stop");
                check_teleroom();
                tell_object(me,YEL + "维修完毕，开放使用！\n" + NOR); 
        } else {
                set("do_stop", 1);

                remove_call_out("check_teleroom");
                usrs = query("tele_users");
                if (sizeof(usrs)) {
                        ks = keys(usrs);
                        for(count=sizeof(ks); count > 0; count--)
                        {
                                //tell_object(find_player("redl"), sprintf("%s\n", ks[count-1])); 
                                switch ( is_area(query("tele_users/" + ks[count-1])) ) {
                                        case -1 :
                                        case 0 :
                                                delete("tele_users/" + ks[count-1]);
                                                break;
                                        case 1 : 
                                        default :
                                                ob = query("tele_users/" + ks[count-1])["ob"];
                                                if (ob && playerp(ob)) {
                                                        do_tell_back(ob);
                                                }
                                                break;
                                }
                        }
                }
                message_vision(append_color(NOR + CYN + "$N大声宣布：法阵开始维修，暂缓使用。\n" + NOR, CYN), me);
        }
        
        return 1;
}

int valid_leave(object me, string dir)
{
        object room, *inv;
        int countp;
        int value, i = sizeof(sign);

        if (!interactive(me) || !playerp(me)) return 0;
        
        if (query("do_stop") && wiz_level(me) < 5 && dir != "southeast" && dir != "south" && dir != "southwest") 
        {
                tell_object(me, NOR + "这里正在维修，禁止使用！\n" + NOR); 
                return -1;
        }

        if( me->query_condition("killer") ) {
                tell_object(me, NOR"你正在被通缉，无法进入飞星阵！\n"NOR);
                return -1;
        }

                        inv = deep_inventory(me);
                        if( sizeof(inv) > 0  && wiz_level(me) < 5 && dir != "southeast" && dir != "south" && dir != "southwest") {
                                        foreach( object ob2 in inv ) {
                                        if( ob2->is_character() && base_name(ob2)!="/clone/user/baby" ) {
                                        message_vision(append_color(NOR + CYN + "几个机关人冲上来围住$N，指了指他身上的$n。\n" + NOR, CYN), me, ob2);
                                return -1;
                                        }
                                        }
                                  }
        
                if (query("exits/" + dir)) room = get_object(query("exits/" + dir));
                if (room && objectp(room) && query("max_carry_user", room)) {//限制人数
                        inv = all_inventory(room);
                        if( sizeof(inv) > 0 ) {
                foreach( object ob3 in inv ) {
                        if ( playerp(ob3) && wiz_level(ob3) < 5 ) countp ++;
                }
                }

                if(query("max_carry_user", room) < countp + 1 && wiz_level(me) < 5) {
                                tell_object(me, "你发现对面的人太多了，出现空间不稳定的状态，吓得不敢踏进飞星阵。\n");  
                                me->start_busy(2);
                                return -1;      
                }
                }
        
        while(i--){
                if (sign[i]["exit"] && sign[i]["exit"]==dir) {
                        value = sign[i]["val"];
                        break;
                }
        }        
        
        if (value && wiz_level(me) < 5){
        //if (wiz_level(me) < 5){       
                if (query_temp("teleportroom/put_value", me) < value) {
                        message_vision(append_color(NOR + CYN + "几个机关人冲上来围住$N，指了指石台上的孔" + HIK + "(你的钱没缴够，look kong看清楚价格)" + NOR + CYN + "。\n" + NOR, CYN), me);
                me->start_busy(3);
                        return -1;
                }
                else {
                        addn_temp("teleportroom/put_value", -value, me);
                        if (sign[i]["loop"]) {
                                set("tele_users/" + query("id", me), ([ "ob"    :       me, 
                                                                                                             "cost"  :       value,
                                                                                                             "path"  :       sign[i]["loop"],
                                                                                                             "time"  :       time()
                                                                                                      ]));
                        }
                        do_tell_val(me);
                        message_vision(append_color(NOR + CYN + "$N" + (random(2) ? "轻轻" : "纵身") + "跳上" + (random(2) ? "石台" : "法阵") + "，电闪雷鸣" + (random(2) ? "一声霹雳响" : "一道极光里") + "，$N的身影" + (random(2) ? "消失" : "遁去") + "。\n" + NOR, CYN), me);
                        return 1;
                }
        }
        
        return ::valid_leave(me, dir);
}

void create()
{
        set("short", HIG "飞星法阵" NOR);
        set ("long", NOR
"这里是一个特殊的阵法空间，八根巨大的石柱擎天而立，石柱中\n"
"央漆黑一团，周围闪烁着紫色白色黄色的电蛇。法阵外缘的石台正中\n"
"间有个小孔("CYN"kong"NOR")，边上站着几个傀儡机关人。\n"NOR
        );
                set("exits",([ /* sizeof() == 1 */
                        "south" : "/d/city/kedian4",
                        "southeast" : "/d/city/qiyuan/xxzl1",
                        "southwest" : "/u/redl/school/gate",
                ]));

        set("objects", ([ 
//                                                "/u/redl/teleport/npc/tester" : 1,
        ])); 
        
        set("item_desc", ([
                "孔": (: look_kong :),
                "kong": (: look_kong :),
        ]) );
        set("no_dazuo",1);
        set("no_kill",1);
        set("no_fight",1);
        set("no_steal",1);
        set("no_beg",1);         
                set("no_rideto", 1);
                set("no_flyto", 1);
                set("no_magic", 1); 
        set("no_sleep_room", 1); 
        setup();
        create_exit();
        check_teleroom();
}



