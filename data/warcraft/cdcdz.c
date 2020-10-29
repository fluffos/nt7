// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("翻江搅海[2;37;0m[2;37;0m", ({"czzq"}));        
        set("gender", "男性");                
        set("long", "翻江搅海[2;37;0m
它是玄道具的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "cdcdz");
        set("owner_name", "玄道具");
        set_temp("owner", "cdcdz");
        set_temp("owner_name", "玄道具");
        ::setup();
}
