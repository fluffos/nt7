// save.c
// Written by akuma
// Rewritten by Lonely@nitan.org

#define ORIGINAL_DATA "original_data"

nosave string line = "";
void get_inventory(object ob, int deep)
{
    mixed *inv;
    int i, j, size;
    string ex2, ex3;
    string file;

    j = 0;
    inv = all_inventory(ob);
    size = sizeof(inv);
    ex2 = sprintf("%c", 2);
    for (i = size - 1; i >= 0; i--)
    {

        if (inv[i]->query_autoload() && !deep)
        {
            if (inv[i]->is_container() && j++ < 4)
                get_inventory(inv[i], deep + 1);
            continue;
        }

        if (!inv[i]->is_character() && !inv[i]->is_no_clone() && !query("maze_item", inv[i]) && !inv[i]->is_task() &&
            !inv[i]->query_unique() && !query("no_save", inv[i]))
        {
            //if( mapping_eqv(get_object(inv[i])->query_entire_dbase(), inv[i]->query_entire_dbase()) ) {
            if (query("set_data", inv[i]) || query("equipped", inv[i]))
            { // 降低计算复杂度
                file = save_variable(inv[i]->query_entire_dbase());
                file = replace_string(file, "\n", ex2);
            }
            else
                file = ORIGINAL_DATA;

            line += sprintf("%d%c%s%c%s%c%d%c%s\n",
                            deep, 1, base_name(inv[i]), 1, file, 1, inv[i]->query_amount(), 1, save_variable(inv[i]->my_id()));
        }

        if (inv[i]->is_container() && deep < 3 && j++ < 4)
            get_inventory(inv[i], deep + 1);
    }
}

int save()
{
    string file;
    int deep;
    int ret = 0;

    if (stringp(file = this_object()->query_save_file()))
    {
        assure_file(file + __SAVE_EXTENSION__);

        if (playerp(this_object()))
        {
#ifdef QUIT_SAVE_ALL
            deep = 0;
            line = "";
            get_inventory(this_object(), deep);
            assure_file(file + ".package" + __SAVE_EXTENSION__);
            ret = write_file(file + ".package" + __SAVE_EXTENSION__, line, 1);
#else
            if (this_object()->quit_save_srv())
            {
                deep = 0;
                line = "";
                get_inventory(this_object(), deep);
                assure_file(file + ".package" + __SAVE_EXTENSION__);
                ret = write_file(file + ".package" + __SAVE_EXTENSION__, line, 1);
            }
            else
            {
                write_file(file + ".package" + __SAVE_EXTENSION__, "", 1);
            }
#endif
        }
        ret += save_object(file);
        return ret;
    }

    return 0;
}
int restore()
{
    string file;

    if (stringp(file = this_object()->query_save_file()))
    {
        // debug_message(file);
        return restore_object(file);
    }
    return 0;
}

// logind.c 调用
int restore_package()
{
    string file;
    mixed *efile;
    mixed *ab;
    string ex1, ex2;
    string equipped;
    mixed tmp;
    object *pac = allocate(255);
    int size;
    int i;
    object ob, shadow_ob;

    if (stringp(file = this_object()->query_save_file()))
    {
        file += ".package" + __SAVE_EXTENSION__;
        if (file_size(file) <= 1)
            return 0;

        ex1 = sprintf("%c", 1);
        ex2 = sprintf("%c", 2);
        efile = explode(read_file(file), "\n");
        size = sizeof(efile);
        pac[0] = this_object();
        for (i = 0; i < size; i++)
        {
            file = replace_string(efile[i], ex2, "\n");
            ab = explode(file, ex1);
            ob = new (ab[1]);
            if (!ob)
            {
                log_file("restore_package", query("id") + ":" + ab[1] + "\n");
                continue;
            }
            pac[atoi(ab[0]) + 1] = ob;

            if (ab[2] != ORIGINAL_DATA)
            {
                tmp = restore_variable(ab[2]);
                if (!tmp || !mapp(tmp))
                {
                    log_file("restore_package", query("id") + ":" + ab[2] + "\n");
                    continue;
                }

                ob->set_dbase(copy(tmp));
                if (!undefinedp(ab[4]) && ab[4] != "" && ab[4] != 0)
                {
                    ob->set_name(query("name", ob), restore_variable(ab[4]));
                }
                if (shadow_ob = ob->query_default_object())
                {
                    set("shadow_ob", shadow_ob, ob);
                }
            }

            if (ob->query_amount())
                ob->set_amount(atoi(ab[3]));

            equipped = query("equipped", ob);
            switch (equipped)
            {
            case "worn":
                delete ("equipped", ob);
                ob->move(this_object());
                ob->wear();
                break;
            case "wielded":
                delete ("equipped", ob);
                ob->move(this_object());
                ob->wield();
                break;
            default:
                ob->move(pac[atoi(ab[0])]);
                break;
            }
        }
        return 1;
    }
    else
    {
        return 0;
    }
    return 0;
}
