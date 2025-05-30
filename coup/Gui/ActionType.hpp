/**
 * @file ActionType.hpp
 * @author Gal Maymon
 */

#pragma once


enum class ActionType {
    None,
    Arrest,
    Sanction,
	BlockTax,
	SpyPeek,
    Coup,
    BlockCoup,    // חדש
    BlockBribe
};
