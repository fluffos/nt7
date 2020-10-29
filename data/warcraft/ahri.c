// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m九尾[1;32m狐狸[2;37;0m[2;37;0m", ({"ahria"}));        
        set("gender", "女性");                
        set("long", "阿[2;37;0m
它是阿狸的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ahri");
        set("owner_name", "阿狸");
        set_temp("owner", "ahri");
        set_temp("owner_name", "阿狸");
        ::setup();
}
