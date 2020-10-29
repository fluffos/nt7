// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("武当猛虎[2;37;0m[2;37;0m", ({"wudangtiger"}));        
        set("gender", "男性");                
        set("long", "武当猛虎[2;37;0m
它是捂江米的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "wudangmi");
        set("owner_name", "捂江米");
        set_temp("owner", "wudangmi");
        set_temp("owner_name", "捂江米");
        ::setup();
}
