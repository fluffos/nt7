// haha
// f.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object obj;
        string objname, ownerid;
        string ultimate;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        if (! arg) return notify_fail("指令格式: setultimate obj to LV10|LV69|LV87|LV105|LV121\n");

        if (sscanf(arg, "%s to %s", objname, ultimate) != 2)
                return notify_fail("指令格式: setultimate obj to LV10|LV69|LV87|LV105|LV121\n");

        obj = present(objname, environment(me));
        if (! obj) obj = present(objname, me);
        if (! obj) return notify_fail("找不到指定的物件。\n");

        ownerid = obj->item_owner();

        if (ultimate == "LV10")
        {
                set("combat/MKS", 2100, obj);
                set("owner/"+ownerid, 21000000, obj);
                set("magic/imbue_ok", 1, obj);
                set("magic/blood", 21000, obj);
                set("enchase/flute", 9, obj); 
                obj->save();

                tell_object(me, "设置 " + obj->short() + " 等级为 LV10 成功。\n");
                return 1;
        } else
        if (ultimate == "LV69")
        {
                set("ultimate/37", 1, obj);
                set("ultimate/39", 1, obj);
                set("enchase/flute", 7, obj);
                set("enchase/SN", 69, obj);
                IDENTIFY_D->identify_ultimate_ob(obj, 1);
                obj->save();

                tell_object(me, "设置 " + obj->short() + " 等级为 LV69 成功。\n");
                return 1;
        } else
        if (ultimate == "LV87")
        {
                set("ultimate/37", 1, obj);
                set("ultimate/39", 1, obj);

                if( query("skill_type", obj )
                ||  obj->is_unarmed_weapon() )
                {
                        set("combat/MKS", 2100, obj);
                        set("owner/"+ownerid, 21000000, obj);
                        set("magic/imbue_ok", 1, obj);
                        set("magic/blood", 21000, obj);
                        set("enchase/flute", 9, obj);
                }
                else
                        set("enchase/flute", 7, obj);

                set("enchase/SN", 87, obj);
                set("enchase/wash", 30+random(10), obj);
                IDENTIFY_D->identify_ultimate_ob(obj, 1);
                obj->save();

                tell_object(me, "设置 " + obj->short() + " 等级为 LV87 成功。\n");
                return 1;
        } else
        if (ultimate == "LV105")
        {
                set("combat/MKS", 2100, obj);
                set("owner/"+ownerid, 21000000, obj);
                set("magic/imbue_ok", 1, obj);
                set("magic/blood", 21000, obj);
                set("ultimate/37", 1, obj);
                set("ultimate/39", 1, obj);
                set("enchase/flute", 9, obj);
                set("enchase/SN", 105, obj);
                set("enchase/wash", 60+random(10), obj);
                IDENTIFY_D->identify_ultimate_ob(obj, 1);
                obj->save();

                tell_object(me, "设置 " + obj->short() + " 等级为 LV105 成功。\n");
                return 1;
        } else
        if (ultimate == "LV121")
        {
                set("combat/MKS", 2100, obj);
                set("owner/"+ownerid, 21000000, obj);
                set("magic/imbue_ok", 1, obj);
                set("magic/blood", 21000, obj);
                set("ultimate/37", 1, obj);
                set("ultimate/39", 1, obj);
                set("enchase/flute", 9, obj);
                set("enchase/SN", 121, obj);
                IDENTIFY_D->identify_ultimate_ob(obj, 1);
                obj->save();

                tell_object(me, "设置 " + obj->short() + " 等级为 LV105 成功。\n");
                return 1;
        } else  return notify_fail("等级格式有LV10/LV69/LV87/LV105/LV121，你要设置他为哪个等级？\n");
}
