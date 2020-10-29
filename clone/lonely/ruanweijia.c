 //ruanweijia.c
 //桃花岛宝物-软猬甲
 //PLZW 2003-12-22
 
#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
        set_name(NOR + CYN "软猬甲" NOR, ({ "ruanwei jia", "ruanwei", "jia" }));
        set_weight(8000);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "件");
                set("long", NOR + CYN "
这是一件黑黝黝的软甲，粗看下毫不起眼。这便是桃花岛至宝
软猬甲，只见整个甲身乌黑亮泽，着手柔软，却又是坚硬胜铁，
宝甲外围还生满了倒刺，尖利无比。\n" NOR);
                set("value", 100000);
                set("no_sell", "这是啥？黑不溜秋的。");
                set("material", "cloth");
                set("armor_prop/armor", 150);
                set("stable", 100);
        }
        setup();
}

mixed valid_damage(object ob, object me, int damage)
{
        if( !query_temp("weapon", ob )
            && !query_temp("secondary_weapon", ob )
            && !random(query("score", ob))<100000
           && random(20) == 1)
        {
                ob->receive_damage("qi", damage, me);
                ob->receive_wound("qi", damage * 2 / 3, me);

                return ([ "damage" : -damage,
                          "msg" : HIR "$N" HIR "一招刚触及$n" HIR "身体，忽觉"
                                  "掌心一阵刺痛，大惊之下连忙缩手。\n" NOR ]);
        }
}

void start_borrowing() 
{ 
         remove_call_out("return_to_huang"); 
         call_out("return_to_huang", 7200 + random(600)); 
} 
  
void return_to_huang() 
{ 
      object me; 

      me = environment(); 
      if (! objectp(me)) 
              return; 

      while (objectp(environment(me)) && ! playerp(me)) 
              me = environment(me); 

      if (playerp(me)) 
      { 
              if (me->is_fight()) 
              { 
                      call_out("return_to_zhang", 1); 
                      return; 
              } 

              message_vision("忽然一个桃花弟子走了过来，看到$N，忙招呼道：“黄岛主让我来找你拿回" 
                             "软猬甲，你现在不用了么？”\n" 
                             "$N道：“好了，好了，你就拿回去吧。”\n" 
                             "$N将软猬甲脱下交给桃花弟子带走。\n", me); 
      } else 
      { 
              message("visoin", "忽然一个桃花弟子走了过来，捡起软猬甲，叹了口气，摇摇头走了。\n", 
                      me); 
      } 

      destruct(this_object()); 
} 