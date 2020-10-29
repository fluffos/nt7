// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m虞珞[2;37;0m[2;37;0m", ({"pony"}));        
        set("gender", "女性");                
        set("long", "集勇气、智慧、与美丽于一身的强大生物[2;37;0m
它是慕容雪的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "murong");
        set("owner_name", "慕容雪");
        set_temp("owner", "murong");
        set_temp("owner_name", "慕容雪");
        ::setup();
}
