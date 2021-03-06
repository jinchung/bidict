:class:`~bidict.OrderedBidict`
------------------------------

For those times when your one-to-one mapping must also support
remembering the order in which items were inserted
(à la :class:`collections.OrderedDict`),
:class:`bidict.OrderedBidict` has got your back::

    >>> from bidict import OrderedBidict
    >>> element_by_symbol = OrderedBidict([
    ...     ('H', 'hydrogen'), ('He', 'helium'), ('Li', 'lithium')])
    >>> element_by_symbol.inv
    OrderedBidict([('hydrogen', 'H'), ('helium', 'He'), ('lithium', 'Li')])
    >>> first, second, third = element_by_symbol.values()
    >>> first
    'hydrogen'
    >>> second
    'helium'
    >>> third
    'lithium'
    >>> element_by_symbol.inv['beryllium'] = 'Be'
    >>> last = next(reversed(element_by_symbol))
    >>> last
    'Be'

The additional methods of :class:`~collections.OrderedDict` are supported too::

    >>> element_by_symbol.popitem(last=True)
    ('Be', 'beryllium')
    >>> element_by_symbol.popitem(last=False)
    ('H', 'hydrogen')
    >>> element_by_symbol['H'] = 'hydrogen'
    >>> element_by_symbol
    OrderedBidict([('He', 'helium'), ('Li', 'lithium'), ('H', 'hydrogen')])
    >>> element_by_symbol.move_to_end('Li')  # works on Python < 3.2 too
    >>> element_by_symbol
    OrderedBidict([('He', 'helium'), ('H', 'hydrogen'), ('Li', 'lithium')])
    >>> element_by_symbol.move_to_end('H', last=False)
    >>> element_by_symbol
    OrderedBidict([('H', 'hydrogen'), ('He', 'helium'), ('Li', 'lithium')])

As with :class:`~collections.OrderedDict`,
updating an existing item preserves its position in the order,
while deleting an item and re-adding it moves it to the end::

    >>> element_by_symbol['He'] = 'HELIUM'
    >>> element_by_symbol
    OrderedBidict([('H', 'hydrogen'), ('He', 'HELIUM'), ('Li', 'lithium')])
    >>> del element_by_symbol['H']
    >>> element_by_symbol['H'] = 'hydrogen'
    >>> element_by_symbol
    OrderedBidict([('He', 'HELIUM'), ('Li', 'lithium'), ('H', 'hydrogen')])

When setting an item whose key duplicates that of an existing item
and whose value duplicates that of a different existing item,
the existing item whose value is duplicated will be dropped
and the existing item whose key is duplicated
will have its value overwritten in place::

    >>> o = OrderedBidict([(1, 2), (3, 4), (5, 6), (7, 8)])
    >>> o.forceput(3, 8)
    >>> o
    OrderedBidict([(1, 2), (3, 8), (5, 6)])
    >>> o = OrderedBidict([(1, 2), (3, 4), (5, 6), (7, 8)])
    >>> o.forceput(5, 2)
    >>> o
    OrderedBidict([(3, 4), (5, 2), (7, 8)])


.. _eq-order-insensitive:

:meth:`~bidict.FrozenOrderedBidict.__eq__` is order-insensitive
###############################################################

To ensure that equality of bidicts is transitive,
and to comply with the
`Liskov substitution principle <https://en.wikipedia.org/wiki/Liskov_substitution_principle>`_,
equality tests between an ordered bidict and other
:class:`~collections.abc.Mapping`\s
are always order-insensitive::

    >>> from bidict import bidict
    >>> b = bidict([('one', 1), ('two', 2)])
    >>> o1 = OrderedBidict([('one', 1), ('two', 2)])
    >>> o2 = OrderedBidict([('two', 2), ('one', 1)])
    >>> b == o1
    True
    >>> b == o2
    True
    >>> o1 == o2
    True

For order-sensitive equality tests, use
:meth:`~bidict.FrozenOrderedBidict.equals_order_sensitive`::

    >>> o1.equals_order_sensitive(o2)
    False
    >>> from collections import OrderedDict
    >>> od = OrderedDict(o2)
    >>> o1.equals_order_sensitive(od)
    False

Note that this differs from the behavior of
:meth:`collections.OrderedDict.__eq__`,
by recommendation of Raymond Hettinger himself.

:class:`~bidict.OrderedBidict` also comes in a frozen flavor.
See the :class:`~bidict.FrozenOrderedBidict`
API documentation for more information.
