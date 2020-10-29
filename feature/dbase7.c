// dbase.c

#include <dbase.h>

inherit F_TREEMAP;

mapping dbase = ([]);
nosave mapping tmp_dbase = ([]);

// The default_ob provides the default values of the dbase. It is set to
// be master copy of an object.
nosave mixed default_ob = 0;

mixed query_default_object() { return default_ob; }

void set_default_object(mixed ob)
{
    // if( geteuid(previous_object()) != ROOT_UID )
    //      error("dbase: Only this_object() or object with root euid can set default_ob.\n");
    if (!geteuid())
        seteuid(getuid());

    if (stringp(ob))
        ob = get_object(ob);

    if (objectp(ob))
    {
        default_ob = ob;
        set("no_clean_up", 1, ob);
        set("shadow_ob", ob);
    }
}

mixed add(string prop, mixed data)
{
    mixed old;

    if (!mapp(dbase) || !(old = query(prop)))
        return set(prop, data);

    if (functionp(old))
        error("dbase: add() - called on a function type property.\n");

    return set(prop, old + data);
}

mapping query_entire_dbase()
{
    // if( (previous_object() != this_object())
    // &&  (geteuid(previous_object()) != ROOT_UID) )
    //      error("dbase: query_entire_dbase() - must has root euid or be this_object().\n");

    return dbase;
}

mixed add_temp(string prop, mixed data)
{
    mixed old;

    if (!mapp(tmp_dbase) || !(old = query_temp(prop)))
        return set_temp(prop, data);

    if (functionp(old))
        error("dbase: add_temp() - called on a function type property.\n");

    return set_temp(prop, old + data);
}

mapping query_entire_temp_dbase()
{
    // if( (previous_object() != this_object())
    // &&  (geteuid(previous_object()) != ROOT_UID) )
    //      error("dbase: query_entire_temp_dbase() - must has root euid or be this_object().\n");

    return tmp_dbase;
}

nomask void set_dbase(mapping data)
{
    // if( !is_root(previous_object()) )
    //      return;

    if (!mapp(data))
        return;

    dbase = data;
}

nomask void set_temp_dbase(mapping data)
{
    // if( !is_root(previous_object()) )
    //      return;

    if (!mapp(data))
        return;

    tmp_dbase = data;
}

nomask void delete_all_dbase()
{
    // if( !is_root(previous_object()) )
    //      return;

    dbase = ([]);
}

nomask void delete_all_temp_dbase()
{
    // if( !is_root(previous_object()) )
    //      return;

    tmp_dbase = ([]);
}

/*
varargs int set_shadow_ob(object ob)
{
	if( clonep() )
	{
                if( !objectp(ob) ) ob = load_object(base_name(this_object()));
                //set("shadow_ob", ob || load_object(base_name(this_object())));
                set("shadow_ob", ob);
                default_ob = ob;
                set("no_clean_up", 1, ob);
		return 1;
	}
	return 0;
}

object query_shadow_ob()
{
	return dbase["shadow_ob"];
}
*/
