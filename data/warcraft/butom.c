// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m大肥猪[2;37;0m[2;37;0m", ({"omo"}));        
        set("gender", "女性");                
        set("long", "一头又肥又壮的大肥猪，一看就是猪八戒的兄弟。[2;37;0m
它是周不同的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "butom");
        set("owner_name", "周不同");
        set_temp("owner", "butom");
        set_temp("owner_name", "周不同");
        ::setup();
}
