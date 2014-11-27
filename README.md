SimpleScalar (modified)
=======================

This version of SimpleScalar modified for store memory access trace.

Additional parameter:

`-mtrace filename.mtr` - set filename where **data** memory access trace will be written.

Memory access file
-----------

File has next structure:

`<operation type> <size of block> <address>`

where:

`<operation type>` - type of operation: `l` (load) or `s` (store)

`<size of block>` - size of requested block

`<address>` - address of requested block

Example of access file:

    s 4 2147450736
    s 4 2147450748
    s 4 2147450744
    s 4 2147450740
    l 4 2147450780
    l 4 2147450776
    l 4 2147450772
    l 4 2147450768
    l 4 2147450800
