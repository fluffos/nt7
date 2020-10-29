inherit ITEM;
void create()
{
    set_name("骸骨", ({ "skeleton" }));
    set_weight(500);
    if( clonep() )
        set_default_object(__FILE__);
    else {
        set("unit", "具");
        set("long",
            "一具枯乾的骸骨。\n");
        set("value", 0);
        set("no_get","这东西一碰就散，还是别拣吧！\n");
    }
}