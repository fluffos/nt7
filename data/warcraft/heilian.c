// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m朱雀神鸟[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "女性");                
        set("long", "朱雀神鸟[2;37;0m
它是黑莲的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "heilian");
        set("owner_name", "黑莲");
        set_temp("owner", "heilian");
        set_temp("owner_name", "黑莲");
        ::setup();
}
