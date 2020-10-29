// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("血杀[2;37;0m[2;37;0m", ({"wjy"}));        
        set("gender", "男性");                
        set("long", "血杀[2;37;0m
它是无痕的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wjwj");
        set("owner_name", "无痕");
        set_temp("owner", "wjwj");
        set_temp("owner_name", "无痕");
        ::setup();
}
