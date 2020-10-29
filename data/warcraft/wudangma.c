// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("乌当二米麒麟[2;37;0m[2;37;0m", ({"wudangmiaride"}));        
        set("gender", "男性");                
        set("long", "乌当二米麒麟[2;37;0m
它是捂二米的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wudangma");
        set("owner_name", "捂二米");
        set_temp("owner", "wudangma");
        set_temp("owner_name", "捂二米");
        ::setup();
}
