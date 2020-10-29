#include <armor.h>
#include <ansi.h>

inherit CLOTH;
void check_color(); 
void create()
{
   set_name(YEL "七色霓裳" NOR, ({ "color skirt","skirt" }) );
   set_weight(20);
                set("long", "取彩虹七色，集天地灵气，夜辰妙手织成。 \n");
     set("material", "silk");
     set("unit", "件");
     set("armor_prop/armor",50 ); 
     set("armor_prop/per", 20);
     set("female_only", 100);  
   setup();
         call_out("check_color",3);
  }
 
int query_autoload(){ return 1;}

void init()
{
       object me;
       object ob = this_object();
  
       if (!environment(ob)||!interactive(environment(ob))) {
                 return;
                    }
       me = this_player();
       if (!geteuid(me)||geteuid(me)!="night")  {
       tell_object(me,"七色霓裳化为一道眩目的光华，消失在了空气中。\n");  
                 destruct(ob);
                    } 
      return;
} 

void check_color()
{
     object ob = this_object(); 
  remove_call_out("check_color");
       switch ((int)random(7)) {
           case 0 : 
              set("name", HIG"七色霓裳"NOR, ob);
               break; 
           case 1 : 
              set("name", HIW"七色霓裳"NOR, ob);
               break;
           case 2 :
              set("name", HIR"七色霓裳"NOR, ob);
               break;
           case 3 :
              set("name", HIY"七色霓裳"NOR, ob);
               break;
           case 4 :
              set("name", HIM"七色霓裳"NOR, ob);
               break;
           case 5 :
              set("name", HIC"七色霓裳"NOR, ob);
               break; 
           case 6 :
              set("name", YEL"七色霓裳"NOR, ob);
               break;
           default:
                break;
                   } 
        call_out("check_color",3);
}