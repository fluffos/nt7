// This program is a part of NITAN MudLIB 
// redl 2015/10
#include <ansi.h>
inherit ITEM;

void create() 
{ 
              set_name(NOR HIY "金船" HIC"舱门"NOR, ({"door", "cang men"}) ); 
              if( clonep() ) {
                      destruct(this_object());
              }
              else { 
                        set_weight(100000000000);
                set("long", NOR "这是金船里的暗门，不知道通往哪里。上面有个圆环状的机关，摸摸(touch)试试？\n" NOR);
                set("unit", "道");
                set("value", 1);
                set("no_uget", 1);
                set("no_drop", 1);
                set("no_give", 1);
                set("no_sell", 1);
                set("no_get", 1);
                set("no_steal", 1);
                set("no_beg", 1);
                set("no_put", 1);
                set("no_store", 1);
                set("unique", 1);
                set("no_pawn", 1);
              } 
              setup(); 
} 

int is_attacker(object me)
{
        object *attackers;
        attackers = query("attackers");
        if (!attackers || !sizeof(attackers)) return 0;
        if (member_array(me, attackers)==-1) return 0;
        return 1;
}

int do_touch()
{
        object *attackers;
        object me = this_object();
        object who = this_player();
        object fu;
        int tele_num;
        
        if (who->is_busy())
        {
                tell_object(who, NOR BUSY_MESSAGE NOR); 
                return 1;
        }
        else if (random(3))
                who->start_busy(1);     
                
        if (query("neili", who)<1000000) {
                tell_object(who, NOR "你内力不足。\n" NOR); 
                return 1;
        }
        if (query("jingli", who)<500000) {
                tell_object(who, NOR "你精力不足。\n" NOR); 
                return 1;
        }
        
        message_vision(NOR CYN "$N运转真气到手上，用力去旋扭舱门上的圆环。\n" NOR, who); 
        addn("neili", -100000, who);
        addn("jingli", -50000, who);
        addn("touch_num", 1, me);
        for (int i = 0; i<9; i++)
                if (query("touch_num", me) > 16 << i)
                        set("tele_num", i, me);
        tele_num = query("tele_num", me);
        if (tele_num>0) {
                message_vision(NOR HIW "$N" HIW "上金光闪闪地显出一个字：“" + NOR YEL + ({"","癸","壬","辛","庚","己","戊","丁","丙","乙","甲"})[tele_num] + HIW "”。" + ((!random(5)) ? (NOR + " (push)?"):"") + "\n" NOR, me); 
                if ( !random(200) && (random(who->query_kar())>20) && ((tele_num -1 ) > query("drop_num/fu", me))) {
                        addn("drop_num/fu", 1, me);
                        message_vision(NOR HIW "$N" HIW "duang地掉出一件东西...\n" NOR, me); 
                                        fu = new("/u/redl/teleport/npc/obj/qkfz");
                                        fu->move(environment(me));                      
                }
                
        } else {
                tell_object(who, NOR "圆环抖了一下，似乎加把劲可以一直推下去。\n" NOR); 
        }
        
        attackers = query("attackers");
        if (!attackers || !sizeof(attackers)) attackers = ({});
        if (!is_attacker(who)) {
                attackers += ({who});
                set("attackers", attackers);
        }
        //DEBUG_CHANNEL(query("touch_num", me));        
        return 1;
}

int do_push()
{
        object me = this_object();
        object who = this_player();
        int tele_num;
        
        tele_num = query("tele_num", me);
        if (tele_num<1) {
                tell_object(who, NOR "你推了推舱门，可是什么反应也没有。\n" NOR); 
                return 1;
        }
        message_vision(NOR HIC"\n$N" NOR HIC "使劲一撞" "$n" HIC "滚到了一个不知名的去处。\n\n" NOR, who, me); 
        who->move(get_object("/u/redl/teleport/yuanjiang/chuan7" + (string)tele_num));
        return 1;
}

void init()
{
        object me = this_player();
        if (!playerp(me)) return;
        add_action("do_touch", "touch"); 
        add_action("do_push", "push"); 
}


