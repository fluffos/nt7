// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是大洞洞的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xiangjjjj");
        set("owner_name", "大洞洞");
        set_temp("owner", "xiangjjjj");
        set_temp("owner_name", "大洞洞");
        ::setup();
}
