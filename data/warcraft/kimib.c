// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m冰凤之舞[2;37;0m[2;37;0m", ({"phx"}));        
        set("gender", "女性");                
        set("long", "雪白的凤，翱翔于九天之上的圣灵！[2;37;0m
它是慕容飞雪的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "kimib");
        set("owner_name", "慕容飞雪");
        set_temp("owner", "kimib");
        set_temp("owner_name", "慕容飞雪");
        ::setup();
}
