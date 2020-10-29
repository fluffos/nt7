// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m叁武[2;37;0m[2;37;0m", ({"matjpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是武叁的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "matj");
        set("owner_name", "武叁");
        set_temp("owner", "matj");
        set_temp("owner_name", "武叁");
        ::setup();
}
