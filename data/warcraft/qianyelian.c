// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m观音菩萨莲台[2;37;0m[2;37;0m", ({"guanyinliantai"}));        
        set("gender", "女性");                
        set("long", "$HIW$观音菩萨莲台[2;37;0m
它是乾冶莲的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "qianyelian");
        set("owner_name", "乾冶莲");
        set_temp("owner", "qianyelian");
        set_temp("owner_name", "乾冶莲");
        ::setup();
}
