// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "女性");                
        set("long", "一只麒麟[2;37;0m
它是专用雅人的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "emsz");
        set("owner_name", "专用雅人");
        set_temp("owner", "emsz");
        set_temp("owner_name", "专用雅人");
        ::setup();
}
