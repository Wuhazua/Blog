import { useState, useMemo } from 'react';

const usePagination = (totalItems, itemsPerPage) => {
  const [currentPage, setCurrentPage] = useState(1);

  const totalPages = useMemo(() => Math.ceil(totalItems / itemsPerPage), [
    totalItems,
    itemsPerPage,
  ]);

  const handlePageChange = (pageNumber) => {
    setCurrentPage(pageNumber);
  };

  return {
    currentPage,
    totalPages,
    handlePageChange,
  };
};

export default usePagination;
