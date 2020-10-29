#include <weapon.h>
#include <ansi.h>
inherit BLADE;
inherit F_UNIQUE;
inherit F_NOCLONE;

void return_to_back();
void start_borrowing() 
{
        remove_call_out("return_to_back"); 
        call_out("return_to_back", 3600+random(7200)); 
} 

void create()
{
        set_name(CYN "屠龙刀" NOR, ({ "tulong blade" , "blade" ,"dao", "tulong" }) );
        set_weight(30000);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "柄");
                set("long", HIY "这便是号称武林至尊的屠龙宝刀，四尺来长的单刀，竟达一百多斤之重。\n相传其中藏有旷世的大秘密。\n" NOR);
                set("value", 100000);
                set("no_sell", "这样东西不能卖。\n");
                set("no_store", 1);
                set("rigidity",8000);   
                set("unique", 1);
                set("material", "steel");
                set("wield_msg", HIY "$N一声狂笑，从背后抽出那柄号称“"NOR+HIR"武林至尊"NOR+HIY"”的屠龙宝刀高高举起。\n" NOR);
                set("unwield_msg", HIY "$N哈哈一笑，将屠龙宝刀插回背后。\n"NOR);
        }
        set("enchase/apply_prop", ([
                "add_busy"  : 10,
                "add_weak"  : 40,
                "avoid_locked" : 40,
                "add_damage" : 50,
                "add_skill"  : 200,
        ]));
        init_blade(5000);
        setup();
        start_borrowing();
        check_clone();
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
        int pro;
        int dam;
        dam = me->query_str()*100;
        victim->receive_damage("jing",dam * 2);
        return HIM "屠龙刀夹带着刺耳的破空声划出一道道长虹，$n只感到心神意乱，勉强作出抵挡。\n" NOR;
}

void init()
{
        add_action("do_open","duikan");
}

int do_open(string arg, object me)
{
        object pai,ob;
        if(arg != "yitian sword" || !ob = present("yitian sword", environment(this_object()))) 
        {
                return notify_fail("你要砍什么？\n");
        }
        else if( query("jiali", this_player()) <= 160 )
                return notify_fail(WHT "\n你提起屠龙刀对准倚天剑用力的砍了下去！"NOR+HIR"\n\n只听“镪”的一声脆响，飞溅出几点火星。\n" NOR);
        {
                pai = new("/d/tulong/obj/duan1");
                pai->move(this_player());
                pai = new("/d/tulong/obj/duan2");
                pai->move(this_player());
                pai = new("/d/tulong/obj/zhenjing");
                pai->move(this_player());
                pai = new("/d/tulong/obj/miji");
                pai->move(this_player());
                pai = new("/d/tulong/obj/yishu");
                pai->move(this_player());
                message_vision(WHT "\n$N提起屠龙刀对准倚天剑用力的砍了下去！\n\n"NOR+HIW"只听一声闷响，$N手臂一震，屠龙刀和倚天剑已经断了。你发现刀剑中竟然夹藏着几卷帛绢。\n"NOR,this_player());
                destruct (ob);
                destruct(this_object());
                return 1;
        }
}

void return_to_back() 
{ 
        object me; 

        me = environment(); 
        if (! objectp(me)) 
                return; 

        while (objectp(environment(me)) && ! playerp(me)) 
                me = environment(me); 

        if(base_name(me)=="/d/tulong/tulong/obj/ding")
        {
                call_out("return_to_back",3600+random(3600));
                return ;
        }
        
        if (playerp(me)) 
        { 
                if (me->is_fighting()) 
                { 
                        call_out("return_to_back", 1); 
                        return; 
                } 
                //是否应该执行unwield
                tell_object(me, HIR"\n一条人影从你眼前一闪而过：" +
                            "“多谢替老夫取回" NOR + name() + HIR
                            "，就此谢过，咱们后会有期！”\n\n"NOR);

        } else 
        { 
                message("vision", "忽然一个人走了过来，捡起"+name()+"，叹了口气，摇摇头走了。\n", me); 
        } 

        move("/clone/misc/void");
        call_out("real_back", random(2));
}

void real_back()
{
        object room, ding;

        room = get_object("/d/binghuo/wangpangu2");
        ding = present("ding", room);
        move(ding);
        start_borrowing();
} 