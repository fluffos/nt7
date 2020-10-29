// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("飞红巾[2;37;0m[2;37;0m", ({"fhj"}));        
        set("gender", "女性");                
        set("long", "哦[2;37;0m
它是葫芦金娃的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "hulua");
        set("owner_name", "葫芦金娃");
        set_temp("owner", "hulua");
        set_temp("owner_name", "葫芦金娃");
        ::setup();
}
