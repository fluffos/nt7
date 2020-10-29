// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m白鹤[2;37;0m[2;37;0m", ({"wdyi"}));        
        set("gender", "女性");                
        set("long", "这是一只漂亮的白鹤，翅膀宽阔.....[2;37;0m
它是铁血武一的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "canwda");
        set("owner_name", "铁血武一");
        set_temp("owner", "canwda");
        set_temp("owner_name", "铁血武一");
        ::setup();
}
