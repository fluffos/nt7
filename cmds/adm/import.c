// import.c

#define IP_FILE "/adm/etc/ipdata7"

// #define IP_FILE "/adm/etc/ipdata2"
// #define IP_FILE "/adm/etc/ipdata3"

inherit F_CLEAN_UP;

#include <ansi.h>
#include "/adm/etc/database.h"

void resolve_data(string line);
int main(object me, string arg)
{
        int lines;
        int i;
        string line;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        lines = file_lines(IP_FILE);

        write(HIR "正在转换...\n\n" NOR);
        for (i = 1; i <= lines; i++)
        {
                line = read_file(IP_FILE, i, 1);
                line = line[0..<2];
                resolve_data(line);

                if (i % 100) reset_eval_cost();
        }
        write(HIR "\n一共转换了 " + (i - 1) + " 条 IP 数据。\n" NOR);

        return 1;
}

void resolve_data(string line)
{
        string start, end, desc, addr, place;

        if (sscanf(line, "%s||%s||%s||%s", start, end, place, addr) == 4)
        {
                desc = place + addr;
                /*
                write(sprintf(CYN "INSERT INTO %s "
                              "VALUES (\"%s\", \"%s\", \"%s\")\n" NOR,
                              IP_TABLE, start, end, desc));
                */

                DATABASE_D->db_query(sprintf("INSERT INTO %s "
                                     "VALUES (\"%s\", \"%s\", \"%s\")",
                                     IP_TABLE, start, end, desc));
        }
}

int help()
{
        write(@TEXT
指令格式: import

导入 IP 数据文件。
TEXT);
        return 1;
}
