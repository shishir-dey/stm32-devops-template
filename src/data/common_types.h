/**
 * @file common_types.h
 * @brief Common type definitions for STM32 DevOps Template data structures
 * @details This header provides shared type definitions used across all data
 *          structure implementations to maintain consistency and avoid naming
 *          conflicts between different modules.
 *
 * @author Shishir Dey
 * @date 2025
 * @version 1.0.0
 *
 * @note This file should be included by all data structure headers to ensure
 *       consistent status type definitions across the entire project.
 *
 * @see https://github.com/shishir-dey/stm32-devops-template
 */

#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

/**
 * @defgroup CommonTypes Common Type Definitions
 * @brief Shared type definitions for embedded system data structures
 *
 * This module provides common type definitions that are used across all
 * data structure implementations in the STM32 DevOps Template project.
 * Using common types ensures consistency and prevents naming conflicts.
 * @{
 */

/**
 * @brief Status enumeration for data structure operations
 * @details This enumeration provides a standardized way to indicate the
 *          success or failure of data structure operations across all
 *          implementations in the project.
 *
 * @par Usage Examples:
 *      - Function return values to indicate operation status
 *      - Error checking in calling code
 *      - Status reporting in embedded system diagnostics
 *
 * @note All data structure functions use this enum for consistent error handling
 * @warning Always check return values when calling data structure functions
 */
typedef enum {
    SUCCESS,    /**< Operation completed successfully */
    FAILURE     /**< Operation failed (e.g., queue full, empty, or null pointer) */
} status_t;

/** @} */ // End of CommonTypes group

#endif // COMMON_TYPES_H