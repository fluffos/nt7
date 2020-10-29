// yaolu.c 古墓派药炉
// copy from xkx yaolu.c
// modified by April 2001.09.26
// update by april 2001.11.09

#include <ansi.h>

inherit ITEM;

#include "/d/gumu/obj/drug_list.h"

#define FILE_DIR "/d/gumu/obj/"

#define _DES "一只古墓派特制药炉，青玉石制成，朴实无华。\n炉顶有个石盖(lip)，盖中偏左有一孔，炉下有炭盆，盆内的木炭(coal)看来是新加的。\n"
#define _FIRE HIR"\n药炉下正燃着火。\n"NOR
#define _OPEN "药炉盖子已经揭开。\n"

void create()
{
        set_name(CYN"青石药炉"NOR,( {"yao lu","yaolu","lu"} ));
        set_weight(10000);
        /*if (clonep() )
                set_default_object(__FILE__);
        else*/{
                set("unit","只");
                set("long",_DES);
                set("value",10000);
                set("material","stone");
                set("no_get",1);
                set("cure_s",0);
                set("cure_d",0);
                set("cure_n",0);
                set("count",6);
                set("drug","none");
                set("no_refresh", 1);
        }
        
        setup();
}

void init()
{
        add_action("do_open","open");
        add_action("do_addyao","add");
        add_action("do_close","close");
        add_action("do_pour","dao");
        add_action("do_pour","pour");
        add_action("do_burn","burn");
        add_action("do_miehuo","mie");
        add_action("do_aoyao","aoyao");
        add_action("do_aoyao","lianyao");
        add_action("do_quyao","qu");
}

int do_open(string arg)
{
        object obj,me;
        me = this_player();
        obj = this_object();

        if (arg != "lip") return notify_fail("你要打开什么？\n");
        if (query("open")) return notify_fail("盖子已经打开了。\n");

        if (query("is_burning")){
                message_vision(RED"只听「啊」的一声惨叫，原来$N被药炉烫了手。\n"NOR,me);
                addn("qi",-150+random(50), me);
                set("long",_DES+_FIRE);
                return 1;
        }
        
        message_vision("$N将药炉盖子揭开。\n", me);
        set("long",_DES+_OPEN);
        set("open", 1);

        return 1;
}
        
int do_addyao(string arg)
{
        object me, obj,ob;
        string item, target; 
        int s,d,n;
        me = this_player();
        ob = this_object();

        if (!query("open")) return notify_fail("你先把盖子打开吧。\n"); 

        if (!arg || sscanf(arg, "%s in %s", item, target) != 2 )
                return notify_fail("你要将什么东西放进哪里？\n");

        if (item == "all" ) return notify_fail("这小小药炉怎么装得下这么多东西？\n");
                
        if (!objectp(obj = present(item, me))) return notify_fail("东西呢？\n");
                                                                
        if( !query("yaocai", obj))return notify_fail("药炉里只能放用以炼制的药材。\n");
                        
        if (query("is_burning")) return notify_fail("火已点燃，不要乱动。\n");
                
        if (query("count") < 1) return notify_fail("你已放了太多药材了。\n");

        s=query("cure_s", obj);
        d=query("cure_d", obj);
        n=query("cure_n", obj);

        message_vision("$N把一"+query("unit", obj)+query("name", obj)+"放进药炉。\n",me);
        destruct(obj);
        addn("count",-1);

        addn("cure_s",s);
        addn("cure_d",d);
        addn("cure_n",n);
        
        if (wizardp(me)) printf("%d\t%d\t%d\t\n",query("cure_s"),query("cure_d"),query("cure_n"));

        set("ready", 1);
        return 1;
}

int do_pour(string arg)
{
        object ping,me,box;
        int lvl,i,has_ping;
        object *inv;
        me = this_player();

        if (!query("open"))        return notify_fail("你先把盖子打开吧。\n");

        if (arg == "water")        return notify_fail("难道你想烧开水？\n");

        if (query("is_burning")) return notify_fail("火已点燃，不要乱动。\n");

        if (arg != "玉蜂蜜" && arg != "玉蜂王浆" && arg != "古墓玉浆" && arg != "玉蜂毒")
                return notify_fail("你要添加什么？\n");

        lvl = me->query_skill("qufeng",1);
        if ( lvl < 61
                || ( lvl <  91 && arg == "玉蜂毒" )
                || ( lvl < 121 && arg == "玉蜂王浆" )
                || ( lvl < 151 && arg == "古墓玉浆" ))
                return notify_fail("你的熬药水平不够，还是别浪费了。\n");

        lvl = me->query_skill("yunv-xinjing",1);
        if ( lvl < 61
                || ( lvl < 91 && arg == "玉蜂王浆" )
                || ( lvl < 121 && arg == "古墓玉浆" ))
                return notify_fail("你的内功修为不够，这种药熬不出，还是别浪费了.\n");

        if ( arg == "玉蜂毒" ){
                if ( !box = present("beehive",me) )        return notify_fail("你的玉蜂呢？\n");
                if( query("escaped", box) )
                        return notify_fail("剩下的玉蜂吓得东躲西藏，你一只也抓不到！\n");
                set("escaped", 1, box);
                addn("cure_s",0);
                addn("cure_d",0);
                addn("cure_n",-80);
                message_vision("$N从"+query("name", box)+"中抓了几只玉蜂，滴了几滴玉蜂毒在药炉里。\n",me);
                return 1;
        }

        if (!query("ready")) return notify_fail("你喜欢吃蜜糊？\n");

        has_ping = 0;
        inv = all_inventory(me);
        for(i=0; i<sizeof(inv); i++)
                if( query("name", inv[i]) == CYN"青瓷瓶"NOR
                         && query("liquid/name", inv[i]) == arg
                         && query("liquid/remaining", inv[i]) == 10){
                        has_ping = 1;
                        ping = inv[i];
                }

        if (!has_ping) return notify_fail("你需要一满瓶的"+arg+"来熬药。\n");

        set("liquid/remaining", 0, ping);
        if ( arg == "玉蜂蜜" ) set("mi",1);

        if ( arg == "玉蜂王浆" ) {
                addn("cure_s",70);
                addn("cure_d",70);
                addn("cure_n",-20);
        }
        if ( arg == "古墓玉浆" ) {
                addn("cure_s",90);
                addn("cure_d",90);
                addn("cure_n",-30);
        }
        message_vision("$N从"+query("name", ping)+"中倒了一些"+arg+"在药炉里。\n",me);
        return 1;
}

int do_close(string arg)
{       
        object me;
        me = this_player();

        if (arg != "lip") return notify_fail("你要关闭什么？\n");

        if (!(query("open"))) return notify_fail("盖子已经扣上了。\n");
        if (query("is_burning")){
                message_vision(RED"只听「啊」的一声惨叫，原来$N被药炉烫了手。\n"NOR,me);
        addn("qi", -150+random(50), me);
                set("long",_DES+_OPEN+_FIRE);
                return 1;
        }
        
        message_vision("$N把药炉盖子扣上。\n", me);
        set("long",_DES);
        set("open", 0);
        return 1;
}

int do_burn(string arg)
{
        object me;
        me = this_player();

        if (arg != "coal") return notify_fail("你要点燃什么？\n");

        if (!present("fire",me)) return notify_fail("你用什么点火？\n");

        if (!(query("ready"))) return notify_fail("药炉里什么都没有。\n");

        if (query("is_burning")) return notify_fail("火已经点燃了。\n");
                
        if (query("open")) return notify_fail("你先把盖子盖好吧。\n");

        message_vision(RED"$N将炭盆点燃。\n\n"NOR,me);
        message_vision(HIB"青蓝色的火苗轻轻跳动，将$N的脸映得阴森恐怖。\n"NOR,me);
        set("is_burning", 1);

        if (query("open")) set("long",_DES+_OPEN+_FIRE);
        else set("long",_DES+_FIRE);

        remove_call_out("burning");
        call_out("burning",10+random(5),me);

    return 1;
}

int do_miehuo(string arg)
{
        object me;
        me = this_player();

        if (arg != "huo") return 0;

        if (!(query("is_burning"))) return notify_fail("火还没点燃。\n");
                
        message_vision(RED"$N将炭火熄灭。\n"NOR, me);

        if (query("open")) set("long",_DES+_OPEN);
        else set("long",_DES);

        set("is_burning", 0);
        set("fire_ready", 0);
        remove_call_out("burning");
        return 1;
}

void burning(object me)
{
        if (!query("mi")){
                set("long","一只小巧玲珑的炼药炉。\n");
                message_vision(HIR"突然间药炉内火光大盛，黑烟冒出，$N急忙将火头扑灭。\n"NOR,me);
                message_vision(HIR"$N取出药材一看，已经烧成一团焦炭。\n"NOR,me);
                remove_call_out("renewing");
                call_out("renewing",1,this_object());
                return;
        }

        message_vision("\n"HIY"炭火渐渐明亮，看来可以开始了。\n"NOR,me);
        set("fire_ready", 1);
        return;
}

int do_aoyao()
{
        object me;
        int time,s,d,n,ds,dd,dn,i;
        
        me = this_player();
        time = 0;
        if (!query("fire_ready")) return notify_fail("火侯未到！\n");
        
        if ((int)me->query_skill("qufeng",1) < 60 )
                return notify_fail("你对玉蜂蜜的特性认识不够！\n");

        if( query("neili", me)<500)return notify_fail("你的内力不足！\n");

        if( query("jingli", me)<1000)return notify_fail("你的精力不足！\n");

        s = query("cure_s");
        d = query("cure_d");
        n = query("cure_n");

        if (wizardp(me)) printf("%d\t%d\t%d\t\n\n--------------------\n",s,d,n);

        for (i=0;i<sizeof(drug_list);i++){
                ds = drug_list[i]["s"];
                dd = drug_list[i]["d"];
                dn = drug_list[i]["n"];
                if (wizardp(me)) printf("%d\t%d\t%d\t\n",ds,dd,dn);
                if ( s == ds && d == dd && n == dn ){
                        set("drug",drug_list[i]["file"]);
                        set("drug_name",drug_list[i]["name"]);
                        set("drug_level",drug_list[i]["level"]);
                        time = drug_list[i]["time"];
                        break;
                }
        }

        if ( me->query_skill("qufeng",1) < query("drug_level") )
                return notify_fail("你的熬药知识不够！");
        if ( me->query_skill("yunv-xinjing",1) < query("drug_level")-30 )
                return notify_fail("你的玉女心经修为不够！");

        message_vision(HIC"$N一手靠近炉火一抽一放，借内力操控火势；一手握住药杵，从盖上孔中伸入\n不停搅拌。\n"NOR,me);
        message_vision(HIR"\n$N不停的重复运动，一会儿已是满身大汗。\n"NOR,me);

    if (time == 0) time = 20;
        if (time > 30) me->start_busy(time-random(10));
        else me->start_busy((int)(time/2));

        set("pending", 1);
        remove_call_out("finish");
        call_out("finish",time,me);
        return 1;
}

void finish(object me)
{
        object obj;
        obj = this_object();

        message_vision("\n"HIY"$N深吸一口气，停了下来。\n"NOR,me);
        addn("neili", -(300+random(200)), me);
        addn("jingli", -(500+random(300)), me);
        addn("potential", (query("jingli", me)/200), me);
        addn("combat_exp", (query("neili", me)/500), me);
        set("done", 1);
        set("pending",0);
}

int do_quyao(string arg)
{
        object ob,me,obj,zhen1,zhen2,ping;
        object *inv;
        int i;

        me = this_player();
        obj = this_object();

        if (arg != "yao") return notify_fail("你要取什么？\n");

        if (query("pending")) return notify_fail("你正在运功炼药。\n");

        if (!(query("done"))) return notify_fail("你要取什么？\n");
                
        if (query("is_burning")){
                message_vision(RED"只听「啊」的一声惨叫，原来$N被药炉烫了手。\n"NOR,me);
                addn("qi", -150+random(50), me);
                return 1;
        }

        if (!(query("open"))) return notify_fail("你先把盖子打开吧。\n");

        if (!query("drug") || query("drug") == "none")
                message_vision(HIB"$N开炉一看，炉中之物象一团浆糊一样，看来没什么用。\n"NOR,me);
        else if ( query("drug_name") == "玉蜂针毒" ) {
                if ( !zhen1 = present("jin zhen",me) ) 
                        return notify_fail("你身上没有金针。\n");
                zhen2 = new("/d/gumu/obj/yufeng-zhen");
                zhen2->set_amount(zhen1->query_amount());
                destruct(zhen1);
                zhen2->move(me);
                message_vision("$N取出金针蘸了蘸药炉中熬好的玉蜂毒，放到火上淬火……\n", me);
                message_vision("只听得嗞……，一缕青烟袅袅升起，$N诡异的笑容映着炉火忽明忽暗。\n\n", me);
        }
        else if ( query("drug_name") == "古墓玉浆" || query("drug_name") == "古墓圣浆" ) {
                inv = all_inventory(me);
                for(i=0; i<sizeof(inv); i++){
                        if( query("name", inv[i]) == CYN"青瓷瓶"NOR )
                                if( !query("liquid/remaining", inv[i])){
                                        ping = inv[i];
                                }
                }
                if (!ping) return notify_fail("你需要一个空瓶！\n");
                set("liquid/name", query("drug_name"), ping);
                set("liquid/remaining", 10, ping);
                message_vision("$N将小心地把药炉里的"+query("drug_name")+"斟入青瓷瓶。\n\n", me);
        }
        else{
                ob = new(FILE_DIR+query("drug"));
                message_vision("$N从药炉中取出一"+query("unit", ob)+query("name", ob)+"\n\n",me);
                ob->move(me);
        }

        remove_call_out("renewing");
        call_out("renewing",1,obj);
        return 1;
}

void renewing(object obj)
{
        set("open", 0, obj);
        set("is_burning", 0, obj);
        set("ready", 0, obj);
        set("fire_ready", 0, obj);
        set("pending", 0, obj);
        set("done", 0, obj);
        set("long", _DES, obj);
        set("cure_s", 0, obj);
        set("cure_d", 0, obj);
        set("cure_n", 0, obj);
        set("drug", "none", obj);
        set("count", 6, obj);
}