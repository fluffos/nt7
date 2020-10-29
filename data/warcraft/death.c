// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m睚眦[2;37;0m[2;37;0m", ({"revenge"}));        
        set("gender", "男性");                
        set("long", "龙身豺首,性格刚烈,嗜杀好斗,一饭之德必偿,睚眦之怨必报![2;37;0m
它是死性不改的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "death");
        set("owner_name", "死性不改");
        set_temp("owner", "death");
        set_temp("owner_name", "死性不改");
        ::setup();
}
